#ifndef DIJKSTRAS_PATHPLANNER_HPP
#define DIJKSTRAS_PATHPLANNER_HPP

#include <AStarPathplanner.hpp>

class DijkstrasPathplanner : public AStarPathplanner
{
public:

private:
	float evaluate(Node* to_evaluate_, Node* based_on_) override;

private:
	
};

#endif // DIJKSTRAS_PATHPLANNER_HPP