#ifndef EDGE_HPP
#define EDGE_HPP

#include <array>

class Node;
class Graph;

class Edge
{
	friend class Graph;
public:
							Edge(Node* node1_, Node* node2_);

	const auto&				getNodes() const { return _nodes; }
	float					getWeight() const { return _weight; }

private:
	float 					_weight;
	std::array<Node*, 2> 	_nodes;
	
};

#endif // EDGE_HPP