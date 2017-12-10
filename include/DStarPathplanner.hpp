#pragma once

#include <Pathplanner.hpp>

class DStarPathplanner : public Pathplanner
{
public:
	PathplanningReturnType 	
			operator()(Node* start_, Node* goal_) override;

private:
	float 	processState();
	float 	modifyCost(Node* node1_, Node* node2_, float new_cost);
	float	getMinimumKey() const;
	void	insert(Node* node_, float new_heuristic_);
};
