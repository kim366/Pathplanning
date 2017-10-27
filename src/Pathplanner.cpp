#include <Pathplanner.hpp>

Pathplanner::Pathplanner()
	: _compare{[this] (Node* x_, Node* y_)
	{
		sf::Vector2f value{x_->getPathplanningData().value, y_->getPathplanningData().value};
		if (value.x == value.y && x_ == _goal)
			return false;
		return value.x > value.y;
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