#include <Graph.hpp>
#include <algorithm>
#include <math.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <Gui/Consts.hpp>

Graph::Graph(std::initializer_list<sf::Vector2i> node_positions_,
	std::initializer_list<sf::Vector2i> node_indices_)
{
	for (auto& node_position : node_positions_)
		_nodes.emplace_back(std::make_unique<Node>(static_cast<sf::Vector2f>(node_position)));

	for (auto& node_indices : node_indices_)
		connect(static_cast<sf::Vector2u>(node_indices));
}


void Graph::connect(sf::Vector2u node_indices_)
{	
	auto* node1{getNode(node_indices_.x)};
	auto* node2{getNode(node_indices_.y)};

	sf::Vector2i distance{node1->getPosition() - node2->getPosition()};
	auto weight{std::hypot(distance.x, distance.y)};

	node1->_connections[node2] = weight;
	node2->_connections[node1] = weight;		
}

void Graph::disconnect(sf::Vector2u node_indices_)
{
	auto* node1{getNode(node_indices_.x)};
	auto* node2{getNode(node_indices_.y)};

	node1->_connections.erase(node2);
	node2->_connections.erase(node1);
}

void Graph::createNode(sf::Vector2f position_)
{
	_nodes.emplace_back(std::make_unique<Node>(position_));
}

void Graph::deleteNode(unsigned node_index_)
{
	auto* node{getNode(node_index_)};
	_nodes.erase(std::find_if(begin(_nodes), end(_nodes), [&] (const auto& ptr_) { return ptr_.get() == node; }));
}

void Graph::draw(sf::RenderTarget& target_, sf::RenderStates states_) const
{
	for (const auto& node : _nodes)
	{
		auto flipped_position{node->getPosition()};
		sf::CircleShape visualized_node{Gui::cst::Graph::node_radius};
		visualized_node.setOrigin(Gui::cst::Graph::node_radius, Gui::cst::Graph::node_radius);
		visualized_node.setPosition(flipped_position.x, 500 - flipped_position.y);
		visualized_node.setFillColor(sf::Color::Red);
		target_.draw(visualized_node);
	}
}

void Graph::update(float delta_time_, const Gui::Inputs& inputs_)
{
}
