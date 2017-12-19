#include <Node.hpp>

Node::Node(sf::Vector2f position_)
	: position{position_}
	, tag{New}
	, parent{}
	, value{0}
	, heuristic_value{0}
	, to_start_value{0}
	, previous_heuristic_value{0}
	, key_value{0}
{
}

float getWeight(NodeHandle from_, NodeHandle to_)
{
	const auto found{from_->neighbors.find(to_)};
	if (found != from_->neighbors.end())
		return found->second;
	return std::numeric_limits<float>::infinity();
}

std::vector<NodeHandle> computeSuccessors(NodeHandle node_)
{
	std::vector<NodeHandle> successors;

	for (auto [neighbor, cost] : node_->neighbors)
		if (neighbor != node_)
			successors.push_back(neighbor);
	
	return successors;
}
