#include <Graph.hpp>
#include <algorithm>
#include <math.h>
#include <SFML/System/Vector2.hpp>

void Graph::connect(unsigned node1_index_, unsigned node2_index_)
{	
	auto* node1{_nodes[node1_index_].get()};
	auto* node2{_nodes[node2_index_].get()};

	sf::Vector2i distance{node1->getPosition() - node2->getPosition()};
	auto weight{std::hypot(distance.x, distance.y)};

	node1->_connections[node2] = weight;
	node2->_connections[node1] = weight;		
}

void Graph::disconnect(unsigned node1_index_, unsigned node2_index_)
{
	auto* node1{_nodes[node1_index_].get()};
	auto* node2{_nodes[node2_index_].get()};

	node1->_connections.erase(node2);
	node2->_connections.erase(node1);
}

void Graph::createNode(unsigned x_, unsigned y_)
{
	_nodes.emplace_back(std::make_unique<Node>(sf::Vector2u{x_, y_}));
}

void Graph::deleteNode(unsigned node_index_)
{
	auto* node{_nodes[node_index_].get()};
	_nodes.erase(std::find_if(begin(_nodes), end(_nodes), [&] (const auto& ptr_) { return ptr_.get() == node; }));
}
