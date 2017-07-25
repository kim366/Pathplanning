#ifndef EDGE_HPP
#define EDGE_HPP

class Node;

struct Edge
{
			Edge(Node* node1_, Node* node2_);
	float 	weight;	
	Node* 	_node1;
	Node* 	_node2;
	
};

#endif // EDGE_HPP