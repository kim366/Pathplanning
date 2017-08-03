#include <DijkstrasPathplanner.hpp>

float DijkstrasPathplanner::evaluate(Node* to_evaluate_, Node* based_on_)
{
	return based_on_->value + cost(to_evaluate_, based_on_);
}