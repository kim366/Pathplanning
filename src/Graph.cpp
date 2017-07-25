#include <Graph.hpp>
#include <algorithm>
#include <math.h>
#include <SFML/System/Vector2.hpp>

void Graph::connect(Node* node1_, Node* node2_)
{	
	_edges.emplace_back(std::make_unique<Edge>(node1_, node2_));
	node1_->_edges[node2_] = _edges.back().get();
	node2_->_edges[node1_] = _edges.back().get();		
}

void Graph::disconnect(Node* node1_, Node* node2_)
{
	// Erase-remove idiom 
	_edges.erase(
		std::remove(begin(_edges), end(_edges), std::make_unique<Edge>(*node1_->_edges[node2_])),
		end(_edges));
	node1_->_edges.erase(node2_);
	node2_->_edges.erase(node1_);
}

std::experimental::optional<int> Graph::getWeight(Node* node1_, Node* node2_)
{
	std::experimental::optional<int> weight;

	auto found{node1_->_edges.find(node2_)};

	if (found != end(node1_->_edges))
		weight = found->second->weight;

	return weight;
}

Node* Graph::createNode(unsigned x_, unsigned y_)
{
	_nodes.emplace_back(std::make_unique<Node>(sf::Vector2u{x_, y_}));

	return _nodes.back().get();
}

void Graph::deleteNode(Node* node_)
{
	// Delete Edges connected to node from Graph
	for (auto& edge : node_->_edges)
		_edges.erase(std::remove(begin(_edges), end(_edges), std::make_unique<Edge>(*edge.second)), end(_edges));

	_nodes.erase(std::remove(begin(_nodes), end(_nodes), std::make_unique<Node>(*node_)), end(_nodes));
}
