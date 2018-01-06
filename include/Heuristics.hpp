#pragma once

#include <iostream>
#include <cassert>
#include <math.h>
#include <Grid.hpp>

struct Heuristic
{
	virtual float operator()(NodePtr node_, NodePtr goal_, const Graph& graph_) const = 0;
};

struct Euclidean : Heuristic
{
	float operator()(NodePtr node_, NodePtr goal_, const Graph&) const override
	{
		sf::Vector2f distance{goal_->position - node_-> position}; 
		return std::hypot(distance.x, distance.y);
	}
};

struct None : Heuristic
{
	float operator()(NodePtr, NodePtr, const Graph&) const override
	{
		return 0;
	}
};

struct Manhattan : Heuristic
{
	float operator()(NodePtr node_, NodePtr goal_, const Graph& graph_) const override
	{
		auto grid{dynamic_cast<const Grid*>(&graph_)};
		assert(grid != nullptr);
		assert(!grid->eight_connected);

		sf::Vector2f distance{goal_->position - node_->position};
		return std::abs(distance.x) + std::abs(distance.y);
	}
};

struct Octile : Heuristic
{
	float operator()(NodePtr node_, NodePtr goal_, const Graph& graph_) const override
	{
		auto grid{dynamic_cast<const Grid*>(&graph_)};
		assert(grid != nullptr);
		assert(grid->eight_connected);

		sf::Vector2f distance{goal_->position - node_->position};
		distance = {std::abs(distance.x), std::abs(distance.y)};
		distance /= grid->unit;

		return grid->unit * (distance.x + distance.y) + (grid->diagonal_unit - 2 * grid->unit) * std::min(distance.x, distance.y);
	}
};
