#ifndef ASTAR_PATHPLANNER_HPP
#define ASTAR_PATHPLANNER_HPP

#include <Pathplanner.hpp>

class AStarPathplanner : public Pathplanner
{
public:

	std::experimental::optional<std::pair<std::vector<const Node*>, unsigned>>
			operator()(const Node* start_, const Node* end_) override;

private:
	float	evaluate(Node* to_evaluate_, Node* based_on_) override;
};

#endif // ASTAR_PATHPLANNER_HPP