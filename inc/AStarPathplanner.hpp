#ifndef ASTAR_PATHPLANNER_HPP
#define ASTAR_PATHPLANNER_HPP

#include <Pathplanner.hpp>

class AStarPathplanner : Pathplanner
{
public:
	std::pair<std::vector<Node*>, unsigned>
					operator()(const Node* start_, const Node* end_);

private:
	bool	evaluate(const Node* node_) override;
};

#endif // ASTAR_PATHPLANNER_HPP