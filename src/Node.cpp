#include <Node.hpp>

const auto& Node::getWeight(const Node* node_) const
{
	return _connections[const_cast<Node*>(node_)];
}

void Node::setParent(const Node* node_)
{
	if (!_parent && node_)
	{
		_parent = node_;
	}
}