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
							AStarPathplanner(std::function<float(NodePtr, NodePtr)> heuristic_);
	PathplanningReturnType 	operator()(NodePtr start_, NodePtr goal_) override;

private:
	void					insert(NodePtr node_);
	EvaluationReturnType	evaluate(NodePtr to_evaluate_, NodePtr based_on_) const;
	std::function<float(NodePtr, NodePtr)> 
							_heuristic;
};
