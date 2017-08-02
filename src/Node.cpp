#include <Node.hpp>
#include <algorithm>

const auto& Node::getWeight() const
{
	return _connections[const_cast<Node*>(parent)];
}

std::vector<Node*> Node::expand()
{
	std::vector<Node*> expanded_nodes;

	for (auto& connection : _connections)
		expanded_nodes.push_back(connection.first);

	expanded_nodes.erase(std::find(begin(expanded_nodes), end(expanded_nodes), parent));

	return expanded_nodes;
}