#ifndef ASTAR_PATHPLANNER_HPP
#define ASTAR_PATHPLANNER_HPP

#include <Pathplanner.hpp>

class AStarPathplanner : Pathplanner
{
public:

	std::pair<std::vector<const Node*>, unsigned>
			operator()(const Node* start_, const Node* end_) override;

private:
	bool evaluate(const Node* node1_, const Node* node2_) override;
};

#endif // ASTAR_PATHPLANNER_HPP