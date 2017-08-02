#ifndef ASTAR_PATHPLANNER_HPP
#define ASTAR_PATHPLANNER_HPP

#include <Pathplanner.hpp>

class AStarPathplanner : Pathplanner
{
public:

	std::experimental::optional<std::pair<std::vector<const Node*>, unsigned>>
			operator()(Node* start_, Node* end_) override;

private:
	float	evaluate(const Node* to_evaluate_, const Node* based_on_) override;
};

#endif // ASTAR_PATHPLANNER_HPP