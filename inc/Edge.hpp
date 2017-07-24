#ifndef EDGE_HPP
#define EDGE_HPP

class Node;
class Graph;

class Edge
{
	friend class Graph;

public:
				Edge(Node* node1_, Node* node2_) : _node1(node1_), _node2(node2_) {}

public:
	unsigned 	weight;	

private:
	Node* _node1;
	Node* _node2;
	
};

#endif // EDGE_HPP