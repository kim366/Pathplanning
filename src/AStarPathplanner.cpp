#include <AStarPathplanner.hpp>

std::pair<std::vector<const Node*>, unsigned>
	AStarPathplanner::operator()(const Node* start_, const Node* end_)
{
	std::vector<const Node*> found_path;
	unsigned amount_of_expanded_nodes;

	return std::make_pair(found_path, amount_of_expanded_nodes);
}

bool AStarPathplanner::evaluate(const Node* node1_, const Node* node2_)
{
}