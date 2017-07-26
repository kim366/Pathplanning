#include <math.h>
#include <Edge.hpp>
#include <Node.hpp>

Edge::Edge(Node* node1_, Node* node2_)
{
	nodes[0] = node1_;
	nodes[1] = node2_;

	sf::Vector2i distance{node1_->position - node2_->position};
	
	weight = std::hypot(distance.x, distance.y);
}