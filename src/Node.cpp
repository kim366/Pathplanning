#include <Node.hpp>
#include <algorithm>

const auto& Node::getWeight() const
{
	return _connections[const_cast<Node*>(_parent)];
}

void Node::setParent(const Node* node_)
{
	if (!_parent && node_)
	{
		_parent = node_;
	}
}

std::vector<Node*> Node::expand()
{
	std::vector<Node*> expanded_nodes;

	for (auto& connection : _connections)
		expanded_nodes.push_back(connection.first);

	expanded_nodes.erase(std::find(begin(expanded_nodes), end(expanded_nodes), _parent));

	return expanded_nodes;
}