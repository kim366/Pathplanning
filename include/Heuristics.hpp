#pragma once

#include <assert.h>
#include <math.h>
#include <Grid.hpp>

class Heuristic
{
public:
					Heuristic(Graph& graph_, const Node*& goal_) : _goal(goal_), _graph(graph_) {}
	virtual float 	operator()(const Node* node_) const = 0;

protected:
	const Node*& 	_goal;
	const Graph&	_graph;
};

struct Euclidean : public Heuristic
{
	using Heuristic::Heuristic;

	float operator()(const Node* node_) const override
	{
		sf::Vector2f distance{_goal->getPosition() - node_->getPosition()}; 
		return std::hypot(distance.x, distance.y);
	}
};

struct None : public Heuristic
{
	using Heuristic::Heuristic;

	float operator()(const Node* node_) const override
	{
		return 0.f;
	}
};

struct Manhattan : public Heuristic
{
	using Heuristic::Heuristic;

	float operator()(const Node* node_) const override
	{
		auto grid{dynamic_cast<const Grid*>(&_graph)};
		assert(grid);

		sf::Vector2f distance{_goal->getPosition() - node_->getPosition()};

		distance = {std::abs(distance.x), std::abs(distance.y)};

		return grid->unit * (distance.x + distance.y);
	}
};

struct Octile : public Heuristic
{
	using Heuristic::Heuristic;

	float operator()(const Node* node_) const override
	{
		auto grid{dynamic_cast<const Grid*>(&_graph)};
		assert(grid);
		assert(grid->eight_connected);

		sf::Vector2f distance{_goal->getPosition() - node_->getPosition()};

		distance = {std::abs(distance.x), std::abs(distance.y)};

		return grid->unit * std::max(distance.x, distance.y) + (grid->diagonal_unit - 1) * std::min(distance.x, distance.y);
	}
};

