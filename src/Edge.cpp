#include <math.h>
#include <Edge.hpp>
#include <Node.hpp>

Edge::Edge(Node* node1_, Node* node2_)
{
	_nodes[0] = node1_;
	_nodes[1] = node2_;

	sf::Vector2i distance{node1_->getPosition() - node2_->getPosition()};
	
	_weight = std::hypot(distance.x, distance.y);
}