#pragma once

#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <optional>
#include <Node.hpp>

struct PathplanningReturnType
{
	std::vector<Node*>	path;
	std::set<Node*>	 	examined_nodes;
};

class Pathplanner
{
public:
											Pathplanner();
	virtual									~Pathplanner() = 0;

	virtual PathplanningReturnType 			operator()(int start_index_, int goal_index_) = 0;

protected:
	const std::function<bool(Node*, Node*)>	_compare;
					
	std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>>
											_open{_compare};
	Node*									_start;
	Node*									_goal;
};

