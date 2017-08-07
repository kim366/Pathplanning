#ifndef D_STAR_PATHPLANNER_HPP
#define D_STAR_PATHPLANNER_HPP

class DStarPathplanner
{
public:
	std::pair<std::experimental::optional<std::vector<const Node*>>, std::set<const Node*>>
			operator()(const Node* start_, const Node* end_) override;

private:
	float processState();
	float modifyCost(Node* node1_, Node* node2_, float new_cost);
};

#include <DStarPathplanner.inl>

#endif // D_STAR_PATHPLANNER_HPP