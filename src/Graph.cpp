#include <Graph.hpp>
#include <algorithm>
#include <math.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
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
	connect(getNode(node_indices_.x), getNode(node_indices_.y));
}

void Graph::disconnect(sf::Vector2u node_indices_)
{
	disconnect(getNode(node_indices_.x), getNode(node_indices_.y));
}

void Graph::connect(Node* node1_, Node* node2_)
{
	sf::Vector2i distance{node1_->getPosition() - node2_->getPosition()};
	auto weight{std::hypot(distance.x, distance.y)};

	node1_->_connections[node2_] = weight;
	node2_->_connections[node1_] = weight;
}

void Graph::disconnect(Node* node1_, Node* node2_)
{
	node1_->_connections.erase(node2_);
	node2_->_connections.erase(node1_);
}

void Graph::createNode(sf::Vector2f position_)
{
	_nodes.emplace_back(std::make_unique<Node>(position_));
}

void Graph::deleteNode(unsigned node_index_)
{
	using std::begin;
	using std::end;

	auto* node{getNode(node_index_)};
	_nodes.erase(std::find_if(begin(_nodes), end(_nodes), [&] (const auto& ptr_) { return ptr_.get() == node; }));
}

void Graph::draw(sf::RenderTarget& target_, sf::RenderStates states_) const
{
	using std::begin;
	using std::end;

	auto visualize_edge{[=] (const auto& node1_, const auto& node2_, sf::Color color_) -> sf::RectangleShape
	{
		sf::Vector2f distance{node2_->getPosition() - node1_->getPosition()};
		sf::RectangleShape visualized_edge{{std::hypot(distance.x, distance.y), Gui::cst::Graph::edge_width}};
		visualized_edge.setOrigin(0, Gui::cst::Graph::edge_width / 2);
		visualized_edge.setPosition(node1_->getPosition());
		visualized_edge.setFillColor(color_);
		visualized_edge.setRotation(std::atan(distance.y / distance.x) * 180u / 3.1415926f);

		if (distance.x < 0)
			visualized_edge.rotate(180);

		return visualized_edge;
	}};

	for (const auto& node : _nodes)
	{
		for (auto& connection : node->_connections)
			target_.draw(visualize_edge(node, connection.first, {222, 228, 223}));
	}

	{
		bool should_draw_path_edges{true};
		std::vector<sf::RectangleShape> path_edges;

		for (const auto& node : _nodes)
		{
			if (node->status == Node::OnPath && node->parent)
			{
				if (node->_connections.find(const_cast<Node*>(node->parent)) != end(node->_connections))
					path_edges.push_back(visualize_edge(node, node->parent, {160, 164, 161}));
				else
				{
					should_draw_path_edges = false;
					break;
				}
			}

		}

		if (should_draw_path_edges)
			for (auto& path_edge : path_edges)
				target_.draw(std::move(path_edge));
	}

	for (const auto& node : _nodes)
	{
		sf::CircleShape visualized_node{Gui::cst::Graph::node_radius};
		visualized_node.setOrigin(Gui::cst::Graph::node_radius, Gui::cst::Graph::node_radius);
		visualized_node.setPosition(node->getPosition());
		
		if (_selected_node && node.get() == _selected_node)
		{
			visualized_node.setOutlineThickness(-2.5f);
			visualized_node.setOutlineColor(sf::Color{186, 182, 96});
		}

		if (node->status == Node::OnPath)
			visualized_node.setFillColor(sf::Color{39, 96, 122});
		else if (node->status == Node::Expanded)
			visualized_node.setFillColor(sf::Color{91, 201, 249});
		else
			visualized_node.setFillColor({173, 72, 87});

		target_.draw(visualized_node);
	}
}

void Graph::update(float delta_time_, const Gui::Inputs& inputs_)
{
	using std::begin;
	using std::end;

	if (inputs_.event.clicked(sf::Mouse::Left))
	{
		auto found{std::find_if(begin(_nodes), end(_nodes), [=] (auto& node_)
		{
			sf::Vector2f distance{static_cast<sf::Vector2f>(inputs_.cursor_position) - node_->getPosition()};
			return std::hypot(distance.x, distance.y) <= Gui::cst::Graph::node_radius;
		})};

		if (found != end(_nodes))
		{
			if (!_selected_node)
				_selected_node = found->get();
			else
			{
				if (!std::isinf((*found)->getWeight(*_selected_node)))
					disconnect(found->get(), *_selected_node);
				else if (_selected_node != found->get())
					connect(found->get(), *_selected_node);

				_selected_node.reset();
			}
		}
		else
			_selected_node.reset();
	}
	
}
