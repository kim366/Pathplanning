#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <memory>
#include <experimental/optional>
#include <Node.hpp>

class Graph
{
public:
	float		getWeight(Node* node1_, Node* node2_);
	void 		connect(unsigned node1_index_, unsigned node2_index_);
	void 		disconnect(unsigned node1_index_, unsigned node2_index_);
	void		createNode(unsigned x_, unsigned y_);
	void		deleteNode(unsigned node_index_);

	const auto* getNode(unsigned node_index_) { return &_nodes[node_index_]; }

private:
	std::vector<std::unique_ptr<Node>>
				_nodes;
};

#endif // GRAPH_HPP