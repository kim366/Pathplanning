#ifndef ASTAR_PATHPLANNER_HPP
#define ASTAR_PATHPLANNER_HPP

#include <Pathplanner.hpp>

template<typename H>
class AStarPathplanner : public Pathplanner
{
public:
			AStarPathplanner(Graph& graph_) : _graph(graph_) {}
	std::pair<std::optional<std::vector<const Node*>>, std::set<const Node*>>
			operator()(const Node* start_, const Node* goal_) override;

private:
	Graph&	_graph;
	std::pair<float, float>
			evaluate(const Node* to_evaluate_, const Node* based_on_) const override;
	H 		_heuristic{_graph, _goal};
};

#include <AStarPathplanner.inl>

#endif // ASTAR_PATHPLANNER_HPP