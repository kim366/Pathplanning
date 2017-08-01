#include <Node.hpp>

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

