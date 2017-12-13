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
							AStarPathplanner(Graph& graph_, std::function<float(const Node*, HeuristicData)> heuristic_);
	PathplanningReturnType 	operator()(int start_index_, int goal_index_) override;

private:
	Graph&					_graph;
	EvaluationReturnType	evaluate(const Node* to_evaluate_, const Node* based_on_) const;
	std::function<float(const Node*, HeuristicData)> 
							_heuristic;
	const HeuristicData		_heuristic_data;
};
