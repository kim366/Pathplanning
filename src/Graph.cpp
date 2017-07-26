#include <Graph.hpp>
#include <algorithm>
#include <math.h>
#include <SFML/System/Vector2.hpp>

void Graph::connect(Node* node1_, Node* node2_)
{	
	_edges.emplace_back(std::make_unique<Edge>(node1_, node2_));
	node1_->edges[node2_] = _edges.back().get();
	node2_->edges[node1_] = _edges.back().get();		
}

void Graph::disconnect(Node* node1_, Node* node2_)
{
	_edges.erase(std::find_if(begin(_edges), end(_edges), [&] (auto& ptr_) { return ptr_.get() == node1_->edges[node2_]; }));
	node1_->edges.erase(node2_);
	node2_->edges.erase(node1_);
}

float Graph::getWeight(Node* node1_, Node* node2_)
{
	return node1_->edges[node2_]->weight;
}

Node* Graph::createNode(unsigned x_, unsigned y_)
{
	_nodes.emplace_back(std::make_unique<Node>(sf::Vector2u{x_, y_}));

	return _nodes.back().get();
}

void Graph::deleteNode(Node* node_)
{
	// Delete Edges connected to node from Graph
	for (auto& edge : node_->edges)
		_edges.erase(std::find_if(begin(_edges), end(_edges), [&] (const auto& ptr_) { return ptr_.get() == edge.second; }));

	_nodes.erase(std::find_if(begin(_nodes), end(_nodes), [&] (const auto& ptr_) { return ptr_.get() == node_; }));
}
