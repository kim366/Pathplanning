#ifndef PATHPLANNER_HPP
#define PATHPLANNER_HPP

#include <vector>
#include <queue>
#include <functional>

class Graph;
class Node;

class Pathplanner
{
public:
	virtual std::pair<std::vector<const Node*>, unsigned>
					operator()(const Node* start_, const Node* end_) = 0;

protected:
	virtual bool	evaluate(const Node* node1_, const Node* node2_) = 0;

protected:
	std::priority_queue<Node*, std::vector<Node*>,
		std::function<bool(const Node*, const Node*)>>
					_open_set{[this] (const Node* node1_, const Node* node2_)
						{ return evaluate(node1_, node2_); }};
	
};

#endif // PATHPLANNER_HPP