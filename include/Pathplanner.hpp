#pragma once

#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <optional>
#include <Node.hpp>

struct PathplanningReturnType
{
	std::vector<const Node*>	path;
	std::set<const Node*> 		examined_nodes;
};

struct EvaluationReturnType
{
	float to_start_value, heuristic_value;
};

class Pathplanner
{
public:
	virtual PathplanningReturnType 
					operator()(const Node* start_, const Node* goal_) = 0;
	virtual			~Pathplanner() = 0;

protected:
	virtual EvaluationReturnType
					evaluate(const Node* to_evaluate_, const Node* based_on_) const = 0;
	float			cost(const Node* from_, const Node* to_) const;

protected:
	const std::function<bool(Node*, Node*)>
					_compare{[this] (Node* x_, Node* y_)
					{
						sf::Vector2f value{x_->getPathplanningData().value, y_->getPathplanningData().value};
						if (value.x == value.y && x_ == _goal)
							return false;
						return value.x > value.y;
					}};
					
	std::priority_queue<Node*, std::vector<Node*>, decltype(_compare)>
					_open{_compare};
	const Node*		_start;
	const Node*		_goal;

public:
	enum Tag
	{
		New,
		Open,
		Closed
	};
};

