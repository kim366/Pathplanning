#ifndef EDGE_HPP
#define EDGE_HPP

#include <array>

class Node;

struct Edge
{
							Edge(Node* node1_, Node* node2_);
	float 					weight;	
	std::array<Node*, 2> 	nodes;
	
};

#endif // EDGE_HPP