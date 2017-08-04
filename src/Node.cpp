#include <Node.hpp>
#include <algorithm>
#include <Pathplanner.hpp>

Node::Node(sf::Vector2u position_)
	: _position(position_)
	, tag(Pathplanner::Tag::New)
{
}

const float Node::getWeight(const Node* to_) const
{
	return _connections[const_cast<Node*>(to_)];
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