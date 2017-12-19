#pragma once

#include <vector>
#include <queue>
#include <functional>
#include <optional>
#include <Node.hpp>
#include <NodeHandle.hpp>

struct PathplanningReturnType
{
	std::vector<NodeHandle>	path, examined_nodes;
};

class Pathplanner
{
public:
									Pathplanner();
	virtual							~Pathplanner() = 0;

	virtual PathplanningReturnType 	operator()(NodeHandle start_, NodeHandle goal_) = 0;

protected:
	const std::function<bool(NodeHandle, NodeHandle)>
									_compare;
					
	std::priority_queue<NodeHandle, std::vector<NodeHandle>, std::function<bool(NodeHandle, NodeHandle)>>
									_open{_compare};
	NodeHandle						_start;
	NodeHandle						_goal;
};
