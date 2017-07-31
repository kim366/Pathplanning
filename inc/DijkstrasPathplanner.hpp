#ifndef DIJKSTRAS_PATHPLANNER_HPP
#define DIJKSTRAS_PATHPLANNER_HPP

#include <AStarPathplanner.hpp>

class DijkstrasPathplanner : public AStarPathplanner
{
public:

private:
	bool evaluate(const Node* node1_, const Node* node2_) override;

private:
	
};

#endif // DIJKSTRAS_PATHPLANNER_HPP