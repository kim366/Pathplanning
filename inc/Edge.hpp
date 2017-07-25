#ifndef EDGE_HPP
#define EDGE_HPP

class Node;

struct Edge
{
			Edge(Node* node1_, Node* node2_);
	float 	weight;	
	Node* 	node1;
	Node* 	node2;
	
};

#endif // EDGE_HPP