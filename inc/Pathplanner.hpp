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
	virtual			~Pathplanner() = 0;

protected:
	virtual float	evaluate(const Node* node_) = 0;

protected:
	std::priority_queue<Node*, std::vector<Node*>,
		std::function<bool(Node*, Node*)>>
					_open_set{[] (Node* x_, Node* y_)
						{ return x_->value > y_->value; }};

};

#endif // PATHPLANNER_HPP