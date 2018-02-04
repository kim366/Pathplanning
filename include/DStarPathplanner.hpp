#pragma once

#include <Pathplanner.hpp>
#include <Graph.hpp>

class DStarPathplanner : public Pathplanner
{
public:
			DStarPathplanner(Graph& graph_);

	PathplanningReturnType 	
			operator()(NodePtr start_, NodePtr goal_) override;
	void	resetResult();

private:
	float 	processNode();
	void 	modifyCost(NodePtr first_, NodePtr second_, float new_cost_);
	float	getMinimumKey() const;
	void	insert(NodePtr node_, float new_heuristic_);

	PathplanningReturnType
			_result;
	Graph	_map;
};
