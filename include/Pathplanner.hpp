#pragma once

#include <vector>
#include <queue>
#include <functional>
#include <optional>
#include <Node.hpp>
#include <NodePtr.hpp>

struct PathplanningReturnType
{
	std::vector<NodePtr> path, examined_nodes;
};

class Pathplanner
{
public:
									Pathplanner(std::function<bool(NodePtr, NodePtr)> compare_);
	virtual							~Pathplanner() = 0;

	virtual PathplanningReturnType 	operator()(NodePtr start_, NodePtr goal_) = 0;
	void 							resetOpen();

protected:
	const std::function<bool(NodePtr, NodePtr)>
									_compare;
					
	std::priority_queue<NodePtr, std::vector<NodePtr>, std::function<bool(NodePtr, NodePtr)>>
									_open{_compare};
	NodePtr							_goal;
};
