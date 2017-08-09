#include <Node.hpp>
#include <algorithm>
#include <Pathplanner.hpp>

Node::Node(sf::Vector2u position_)
	: _position(position_)
	, tag(Pathplanner::New)
{
}

const float Node::getWeight(const Node* to_) const
{
	auto found{_connections.find(const_cast<Node*>(to_))};
	if (found != end(_connections))
		return found->second;
	return std::numeric_limits<float>::infinity();
}

std::vector<Node*> Node::expand()
{
	std::vector<Node*> expanded_nodes;

	for (auto& connection : _connections)
	{
		Node* connected_node{connection.first};
		if (connected_node != parent)
			expanded_nodes.push_back(connected_node);
	}

	return expanded_nodes;
}