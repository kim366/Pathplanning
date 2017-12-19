#include <Pathplanner.hpp>

Pathplanner::Pathplanner()
	: _compare{[this] (NodeHandle topmost_, NodeHandle newly_added_) -> bool
	{
		if (topmost_->value == newly_added_->value)
			return newly_added_ == _goal;
		return newly_added_->value < topmost_->value;
	}}
{
}

Pathplanner::~Pathplanner()
{
}
