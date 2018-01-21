#pragma once

#include <iostream>
#include <cassert>
#include <math.h>
#include <Grid.hpp>

struct Heuristic
{
	virtual float operator()(NodePtr node_, NodePtr goal_) const = 0;
};

struct Euclidean : Heuristic
{
	float operator()(NodePtr node_, NodePtr goal_) const override
	{
		sf::Vector2f distance{goal_->position - node_-> position}; 
		return std::hypot(distance.x, distance.y);
	}
};

struct None : Heuristic
{
	float operator()(NodePtr, NodePtr) const override
	{
		return 0;
	}
};

struct Manhattan : Heuristic
{
	float operator()(NodePtr node_, NodePtr goal_) const override
	{
		auto grid{dynamic_cast<const Grid*>(&node_.getGraph())};
		assert(grid != nullptr);
		assert(!grid->eight_connected);

		sf::Vector2f distance{goal_->position - node_->position};
		return std::abs(distance.x) + std::abs(distance.y);
	}
};

struct Octile : Heuristic
{
	float operator()(NodePtr node_, NodePtr goal_) const override
	{
		auto grid{dynamic_cast<const Grid*>(&node_.getGraph())};
		assert(grid != nullptr);
		assert(grid->eight_connected);

		sf::Vector2f grid_distance{goal_->position - node_->position};
		grid_distance = {std::abs(grid_distance.x), std::abs(grid_distance.y)};
		grid_distance /= grid->unit;

		// std::cout << grid->unit * (grid_distance.x + grid_distance.y) + (grid->diagonal_unit - 2 * grid->unit) * std::min(grid_distance.x, grid_distance.y) << " - " << grid->toCoordinate(node_._index).x << ", " << grid->toCoordinate(node_._index).y << '\n';

		return grid->unit * (grid_distance.x + grid_distance.y) + (grid->diagonal_unit - 2 * grid->unit) * std::min(grid_distance.x, grid_distance.y);
	}
};
