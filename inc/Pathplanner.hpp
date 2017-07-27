#ifndef PATHPLANNER_HPP
#define PATHPLANNER_HPP

class Pathplanner
{
public:
								Pathplanner(const Graph&);
	virtual std::vector<Node*> 	findShortestPath(const Node* start_, const Node* end_);

private:
	virtual int 				evaluate(const Node* node_);
	
};

#endif // PATHPLANNER_HPP