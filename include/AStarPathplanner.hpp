#pragma once

#include <Pathplanner.hpp>
#include <Heuristics.hpp>

struct EvaluationReturnType
{
	float to_start_value, heuristic_value;
};

class AStarPathplanner : public Pathplanner
{
public:
							AStarPathplanner(std::function<float(NodeHandle, NodeHandle, const Graph&)> heuristic_, const Graph& graph_);
	PathplanningReturnType 	operator()(NodeHandle start_, NodeHandle goal_) override;
	const std::function<float(NodeHandle, NodeHandle, const Graph&)>&
							getHeuristic() { return _heuristic; }

private:
	EvaluationReturnType	evaluate(NodeHandle to_evaluate_, NodeHandle based_on_) const;
	std::function<float(NodeHandle, NodeHandle, const Graph&)> 
							_heuristic;
	const Graph&			_graph;
};
