#ifndef PATHPLANNER_HPP
#define PATHPLANNER_HPP

#include <vector>

class Graph;
class Node;

class Pathplanner
{
public:
								Pathplanner(const Graph&);
	virtual std::vector<Node*> 	findShortestPath(const Node* start_, const Node* end_);

private:
	virtual bool 				evaluate(const Node* node_);
	
};

#endif // PATHPLANNER_HPP