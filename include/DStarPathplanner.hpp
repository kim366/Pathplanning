#pragma once

#include <AStarPathplanner.hpp>

class DStarPathplanner : public AStarPathplanner
{
public:
			DStarPathplanner(Graph& graph_, std::function<float(const Node*, HeuristicData)> heuristic_);

	PathplanningReturnType 	
			operator()(int start_index_, int goal_index_) override;

private:
	float 	processState();
	float 	modifyCost(Node* node1_, Node* node2_, float new_cost_);
	float	getMinimumKey() const;
	void	insert(Node* node_, float new_heuristic_);

	Graph	_map;
};
