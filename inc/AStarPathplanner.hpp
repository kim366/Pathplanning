#ifndef ASTAR_PATHPLANNER_HPP
#define ASTAR_PATHPLANNER_HPP

#include <Pathplanner.hpp>

template<typename H>
class AStarPathplanner : public Pathplanner
{
public:
	std::pair<std::experimental::optional<std::vector<const Node*>>, std::set<const Node*>>
			operator()(const Node* start_, const Node* end_) override;

private:
	float	evaluate(const Node* to_evaluate_, const Node* based_on_) const override;
	H 		_heuristic{_end};
};

#include <AStarPathplanner.inl>

#endif // ASTAR_PATHPLANNER_HPP