#include <Node.hpp>
#include <algorithm>

const float Node::getWeight() const
{
	return _connections[const_cast<Node*>(parent)];
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