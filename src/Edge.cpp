#include <math.h>
#include <Edge.hpp>
#include <Node.hpp>

Edge::Edge(Node* node1_, Node* node2_)
	: node1(node1_)
	, node2(node2_)
{
	weight = std::hypot(node1_->position.x - node2_->position.x,
		node1_->position.y - node2_->position.y);
}