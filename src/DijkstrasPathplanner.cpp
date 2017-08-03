#include <DijkstrasPathplanner.hpp>

float DijkstrasPathplanner::evaluate(Node* to_evaluate_, Node* based_on_)
{
	return based_on_->value + to_evaluate_->getWeight(based_on_);
}