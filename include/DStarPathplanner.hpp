#pragma once

class DStarPathplanner
{
public:
	std::pair<std::vector<const Node*>, std::set<const Node*>>
			operator()(Node* start_, Node* goal_) override;

private:
	float 	processState();
	float 	modifyCost(Node* node1_, Node* node2_, float new_cost);
};

#include <DStarPathplanner.inl>

