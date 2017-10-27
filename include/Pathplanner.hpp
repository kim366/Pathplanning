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
											Pathplanner();
	virtual									~Pathplanner() = 0;

	virtual PathplanningReturnType 			operator()(const Node* start_, const Node* goal_) = 0;

protected:
	virtual EvaluationReturnType			evaluate(const Node* to_evaluate_, const Node* based_on_) const = 0;
	float									cost(const Node* from_, const Node* to_) const;

protected:
	const std::function<bool(Node*, Node*)>	_compare;
					
	std::priority_queue<Node*, std::vector<Node*>, decltype(_compare)>
											_open{_compare};
	const Node*								_start;
	const Node*								_goal;

public:
	enum Tag
	{
		New,
		Open,
		Closed
	};
};

