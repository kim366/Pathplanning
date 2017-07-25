#include <math.h>
#include <Edge.hpp>
#include <Node.hpp>

Edge::Edge(Node* node1_, Node* node2_)
	: _node1(node1_)
	, _node2(node2_)
{
	weight = std::hypot(node1_->_position.x - node2_->_position.x,
		node1_->_position.y - node2_->_position.y);
}