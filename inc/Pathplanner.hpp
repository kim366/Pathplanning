#ifndef PATHPLANNER_HPP
#define PATHPLANNER_HPP

#include <vector>

class Graph;
class Node;

class Pathplanner
{
public:
	virtual std::pair<std::vector<const Node*>, unsigned>
					operator()(const Node* start_, const Node* end_) = 0;

private:
	virtual bool 	evaluate(const Node* node_) = 0;
	
};

#endif // PATHPLANNER_HPP