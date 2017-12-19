#pragma once

#include <assert.h>
#include <math.h>
#include <Grid.hpp>

struct Heuristic
{
	virtual float operator()(NodeHandle node_, NodeHandle goal_) const = 0;
};

struct Euclidean : Heuristic
{
	float operator()(NodeHandle node_, NodeHandle goal_) const override
	{
		sf::Vector2f distance{goal_->position - node_-> position}; 
		return std::hypot(distance.x, distance.y);
	}
};

struct None : Heuristic
{
	float operator()(NodeHandle node_, NodeHandle goal_) const override
	{
		return 0;
	}
};

struct Manhattan : Heuristic
{
	float operator()(NodeHandle node_, NodeHandle goal_) const override
	{
		sf::Vector2f distance{goal_->position - node_->position};
		return std::abs(distance.x) + std::abs(distance.y);
	}
};

// struct Octile : Heuristic
// {
// 	float operator()(NodeHandle node_, NodeHandle goal_) const override
// 	{
// 		sf::Vector2f distance{data_.goal->getData().position - node_->getData().position};

// 		distance = {std::abs(distance.x), std::abs(distance.y)};

// 		return grid->unit * std::max(distance.x, distance.y) + (grid->diagonal_unit - 1) * std::min(distance.x, distance.y);
// 	}
// };
