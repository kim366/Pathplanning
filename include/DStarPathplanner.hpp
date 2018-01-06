#pragma once

#include <Pathplanner.hpp>
#include <Graph.hpp>

class DStarPathplanner : public Pathplanner
{
public:
			DStarPathplanner(Graph& graph_);

	PathplanningReturnType 	
			operator()(NodePtr start_, NodePtr goal_) override;

private:
	float 	processState();
	float 	modifyCost(NodePtr first_, NodePtr second_, float new_cost_);
	float	getMinimumKey() const;
	void	insert(NodePtr node_, float new_value_);

	PathplanningReturnType
			_result;
	Graph	_map;
};
