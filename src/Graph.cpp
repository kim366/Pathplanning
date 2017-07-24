#include <Graph.hpp>
#include <algorithm>

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