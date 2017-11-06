#include <Pathplanner.hpp>

Pathplanner::Pathplanner()
	: _compare{[this] (Node* topmost_, Node* newly_added_)
	{
		if (topmost_->getPathplanningData().value == newly_added_->getPathplanningData().value)
			return newly_added == _goal;
		return newly_added_ < topmost_;
	}}
{
}

Pathplanner::~Pathplanner()
{
}

float Pathplanner::cost(const Node* from_, const Node* to_) const
{
	return from_->getWeight(to_);
}