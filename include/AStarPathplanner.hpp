#pragma once

#include <Pathplanner.hpp>
#include <Heuristics.hpp>

class AStarPathplanner : public Pathplanner
{
public:
										AStarPathplanner(Graph& graph_, std::function<float(const Node*, HeuristicData)> heuristic_);
	std::pair<std::vector<const Node*>, std::set<const Node*>>
										operator()(const Node* start_, const Node* goal_) override;

private:
	Graph&	_graph;
	std::pair<float, float>				evaluate(const Node* to_evaluate_, const Node* based_on_) const override;
	std::function<float(const Node*, HeuristicData)> 
										_heuristic;
	const HeuristicData					_heuristic_data;
};
