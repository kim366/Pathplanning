#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <memory>
#include <experimental/optional>
#include <Node.hpp>
#include <Edge.hpp>

class Graph
{
public:
	float		getWeight(Node* node1_, Node* node2_); // Invokes undefined behavior if edge non-existant
	void 		connect(Node* node1_, Node* node2_);
	void 		disconnect(Node* node1_, Node* node2_);
	Node*		createNode(unsigned x_, unsigned y_);
	void		deleteNode(Node* node_);

	const auto& getNodes() { return _nodes; }
	const auto& getEdges() { return _edges; }

private:
	std::vector<std::unique_ptr<Node>>
				_nodes;
	std::vector<std::unique_ptr<Edge>>
				_edges;	
};

#endif // GRAPH_HPP