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
							AStarPathplanner(std::function<float(NodePtr, NodePtr, const Graph&)> heuristic_, const Graph& graph_);
	PathplanningReturnType 	operator()(NodePtr start_, NodePtr goal_) override;
	const std::function<float(NodePtr, NodePtr, const Graph&)>&
							getHeuristic() { return _heuristic; }

private:
	EvaluationReturnType	evaluate(NodePtr to_evaluate_, NodePtr based_on_) const;
	std::function<float(NodePtr, NodePtr, const Graph&)> 
							_heuristic;
	const Graph&			_graph;
};
