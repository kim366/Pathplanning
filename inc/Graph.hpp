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
	void 		connect(unsigned node1_index_, unsigned node2_index_);
	void 		disconnect(unsigned node1_index_, unsigned node2_index_);

	void		createNode(unsigned x_, unsigned y_);
	void		deleteNode(unsigned node_index_);

	const auto& getNodes() { return _nodes; }
	const auto& getEdges() { return _edges; }

private:
	std::vector<std::unique_ptr<Node>>
				_nodes;
	std::vector<std::unique_ptr<Edge>>
				_edges;	
};

#endif // GRAPH_HPP