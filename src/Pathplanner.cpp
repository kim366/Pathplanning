#include <Pathplanner.hpp>

Pathplanner::~Pathplanner()
{
}

float Pathplanner::cost(const Node* from_, const Node* to_) const
{
	return from_->getWeight(to_);
}