#include <Pathplanner.hpp>

Pathplanner::Pathplanner()
	: _compare{[this] (Node* topmost_, Node* newly_added_) -> bool
	{
		if (topmost_->getPathplanningData().value == newly_added_->getPathplanningData().value)
			return newly_added_ == _goal;
		return newly_added_->getPathplanningData().value < topmost_->getPathplanningData().value;
	}}
{
}

Pathplanner::~Pathplanner()
{
}

EvaluationReturnType Pathplanner::evaluate(const Node* to_evaluate_, const Node* based_on_) const
{
}
