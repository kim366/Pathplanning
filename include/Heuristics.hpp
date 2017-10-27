#pragma once

#include <assert.h>
#include <math.h>
#include <Grid.hpp>

struct HeuristicData
{
	const Graph& graph;
	const Node*& goal;
};

struct Heuristic
{
	virtual float 	operator()(const Node* node_, HeuristicData data_) const = 0;
};

struct Euclidean : public Heuristic
{
	float operator()(const Node* node_, HeuristicData data_) const override
	{
		sf::Vector2f distance{data_.goal->getData().position - node_->getData().position}; 
		return std::hypot(distance.x, distance.y);
	}
};

struct None : public Heuristic
{
	float operator()(const Node* node_, HeuristicData data_) const override
	{
		return 0.f;
	}
};

struct Manhattan : public Heuristic
{
	float operator()(const Node* node_, HeuristicData data_) const override
	{
		auto grid{dynamic_cast<const Grid*>(&data_.graph)};
		assert(grid);

		sf::Vector2f distance{data_.goal->getData().position - node_->getData().position};

		distance = {std::abs(distance.x), std::abs(distance.y)};

		return grid->unit * (distance.x + distance.y);
	}
};

struct Octile : public Heuristic
{
	float operator()(const Node* node_, HeuristicData data_) const override
	{
		auto grid{dynamic_cast<const Grid*>(&data_.graph)};
		assert(grid);
		assert(grid->eight_connected);

		sf::Vector2f distance{data_.goal->getData().position - node_->getData().position};

		distance = {std::abs(distance.x), std::abs(distance.y)};

		return grid->unit * std::max(distance.x, distance.y) + (grid->diagonal_unit - 1) * std::min(distance.x, distance.y);
	}
};

