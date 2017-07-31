#include <Graph.hpp>
#include <algorithm>
#include <math.h>
#include <SFML/System/Vector2.hpp>

Graph::Graph(std::initializer_list<sf::Vector2i> node_positions_,
	std::initializer_list<sf::Vector2i> node_indices_)
{
	for (auto& node_position : node_positions_)
		_nodes.emplace_back(std::make_unique<Node>(static_cast<sf::Vector2u>(node_position)));

	for (auto& node_indices : node_indices_)
		connect(static_cast<sf::Vector2u>(node_indices));
}


void Graph::connect(sf::Vector2u node_indices_)
{	
	auto* node1{_nodes[node_indices_.x].get()};
	auto* node2{_nodes[node_indices_.y].get()};

	sf::Vector2i distance{node1->getPosition() - node2->getPosition()};
	auto weight{std::hypot(distance.x, distance.y)};

	node1->_connections[node2] = weight;
	node2->_connections[node1] = weight;		
}

void Graph::disconnect(sf::Vector2u node_indices_)
{
	auto* node1{_nodes[node_indices_.x].get()};
	auto* node2{_nodes[node_indices_.y].get()};

	node1->_connections.erase(node2);
	node2->_connections.erase(node1);
}

void Graph::createNode(sf::Vector2u position_)
{
	_nodes.emplace_back(std::make_unique<Node>(position_));
}

void Graph::deleteNode(unsigned node_index_)
{
	auto* node{_nodes[node_index_].get()};
	_nodes.erase(std::find_if(begin(_nodes), end(_nodes), [&] (const auto& ptr_) { return ptr_.get() == node; }));
}
