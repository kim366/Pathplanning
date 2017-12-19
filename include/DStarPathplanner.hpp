#pragma once

#include <Pathplanner.hpp>
#include <Graph.hpp>

class DStarPathplanner : public Pathplanner
{
public:
			DStarPathplanner(Graph& graph_);

	PathplanningReturnType 	
			operator()(NodeHandle start_, NodeHandle goal_) override;

private:
	float 	processState();
	float 	modifyCost(NodeHandle first_, NodeHandle second_, float new_cost_);
	float	getMinimumKey() const;
	void	insert(NodeHandle node_, float new_heuristic_);

	Graph	_map;
};
