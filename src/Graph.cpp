#include <Graph.hpp>
#include <algorithm>
#include <math.h>
#include <SFML/System/Vector2.hpp>

void Graph::connect(unsigned node1_index_, unsigned node2_index_)
{	
	auto* node1 = _nodes[node1_index_].get();
	auto* node2 = _nodes[node2_index_].get();

	_edges.emplace_back(std::make_unique<Edge>(node1, node2));
	node1->_edges[node2] = _edges.back().get();
	node2->_edges[node1] = _edges.back().get();		
}

void Graph::disconnect(unsigned node1_index_, unsigned node2_index_)
{
	auto* node1 = _nodes[node1_index_].get();
	auto* node2 = _nodes[node2_index_].get();

	_edges.erase(std::find_if(begin(_edges), end(_edges), [&] (auto& ptr_) { return ptr_.get() == node1->_edges[node2]; }));
	node1->_edges.erase(node2);
	node2->_edges.erase(node1);
}

float Graph::getWeight(Node* node1_, Node* node2_)
{
	return node1_->_edges[node2_]->_weight;
}

void Graph::createNode(unsigned x_, unsigned y_)
{
	_nodes.emplace_back(std::make_unique<Node>(sf::Vector2u{x_, y_}));
}

void Graph::deleteNode(Node* node_)
{
	// Delete Edges connected to node from Graph
	for (auto& edge : node_->_edges)
		_edges.erase(std::find_if(begin(_edges), end(_edges), [&] (const auto& ptr_) { return ptr_.get() == edge.second; }));

	_nodes.erase(std::find_if(begin(_nodes), end(_nodes), [&] (const auto& ptr_) { return ptr_.get() == node_; }));
}
