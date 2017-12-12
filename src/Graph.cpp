#include <Graph.hpp>
#include <algorithm>
#include <math.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Gui/Consts.hpp>

Graph::Graph(std::initializer_list<sf::Vector2i> node_positions_,
	std::initializer_list<std::pair<int, int>> node_indices_)
{
	for (auto& node_position : node_positions_)
		_nodes.emplace_back(static_cast<sf::Vector2f>(node_position));

	for (auto& node_indices : node_indices_)
		connect(node_indices);
}

int Graph::getIndex(const Node& node_) const
{
	for (int node_index{0}; node_index < _nodes.size(); ++node_index)
		if (node_.getData().position == _nodes[node_index].getData().position)
			return node_index;

	return -1;
}

void Graph::connect(std::pair<int, int> node_indices_)
{
	Node& node1{_nodes[node_indices_.first]};
	Node& node2{_nodes[node_indices_.second]};

	sf::Vector2i distance{node1.getData().position - node2.getData().position};
	auto weight{std::hypot(distance.x, distance.y)};

	node1.getData({}).connections[node_indices_.second] = weight;
	node2.getData({}).connections[node_indices_.first] = weight;
}

void Graph::disconnect(std::pair<int, int> node_indices_)
{
	Node& node1{_nodes[node_indices_.first]};
	Node& node2{_nodes[node_indices_.second]};

	node1.getData({}).connections.erase(node_indices_.second);
	node2.getData({}).connections.erase(node_indices_.first);
}

void Graph::modifyWeight(std::pair<int, int> node_indices_, float new_weight_)
{
	Node& node1{_nodes[node_indices_.first]};
	Node& node2{_nodes[node_indices_.second]};

	node1.getData({}).connections[node_indices_.second] = new_weight_;
	node2.getData({}).connections[node_indices_.first] = new_weight_;
}

void Graph::createNode(sf::Vector2f position_)
{
	_nodes.emplace_back(position_);
}

void Graph::deleteNode(int node_index_)
{
	_nodes.erase(_nodes.begin() + node_index_);
}

void Graph::draw(sf::RenderTarget& target_, sf::RenderStates states_) const
{
	using std::begin;
	using std::end;

	auto visualize_edge{[=] (const auto& node1_, const auto& node2_, sf::Color color_) -> sf::RectangleShape
	{
		sf::Vector2f distance{node2_.getData().position - node1_.getData().position};
		sf::RectangleShape visualized_edge{{std::hypot(distance.x, distance.y), Gui::cst::Graph::edge_width}};
		visualized_edge.setOrigin(0, Gui::cst::Graph::edge_width / 2);
		visualized_edge.setPosition(node1_.getData().position);
		visualized_edge.setFillColor(color_);
		visualized_edge.setRotation(std::atan(distance.y / distance.x) * 180u / 3.1415926f);

		if (distance.x < 0)
			visualized_edge.rotate(180);

		return visualized_edge;
	}};

	for (const auto& node : _nodes)
	{
		for (const auto& [to_node_index, cost] : node.getData().connections)
			target_.draw(visualize_edge(node, _nodes[to_node_index], {98, 100, 98}));
	}

	{
		bool should_draw_path_edges{true};
		std::vector<sf::RectangleShape> path_edges;

		for (const auto& node : _nodes)
		{
			if (node.getVisualization().status == NodeComponents::Visualization::OnPath && node.getPathplanningData().parent != nullptr)
			{
				const int parent_index{getIndex(*node.getPathplanningData().parent)};

				if (node.getData().connections.find(parent_index) != node.getData().connections.end())
					path_edges.push_back(visualize_edge(node, _nodes[parent_index], {47, 48, 47}));
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

	for (int node_index{0}; node_index < _nodes.size(); ++node_index)
	{
		sf::CircleShape visualized_node{Gui::cst::Graph::node_radius};
		visualized_node.setOrigin(Gui::cst::Graph::node_radius, Gui::cst::Graph::node_radius);
		visualized_node.setPosition(_nodes[node_index].getData().position);
		
		if (node_index == _selected_node_index)
		{
			visualized_node.setOutlineThickness(-2.5f);
			visualized_node.setOutlineColor(sf::Color{186, 182, 96});
		}

		if (_nodes[node_index].getVisualization().status == NodeComponents::Visualization::OnPath)
			visualized_node.setFillColor(sf::Color{39, 96, 122});
		else if (_nodes[node_index].getVisualization().status == NodeComponents::Visualization::Examined)
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
			sf::Vector2f distance{static_cast<sf::Vector2f>(inputs_.cursor_position) - node_.getData().position};
			return std::hypot(distance.x, distance.y) <= Gui::cst::Graph::node_radius;
		})};

		if (found != end(_nodes))
		{
			long long int found_node_index{found - begin(_nodes)};

			if (_selected_node_index == -1)
				_selected_node_index = found_node_index;
			else
			{
				if (!std::isinf(getWeight(*this, _nodes[_selected_node_index], *found)))
					disconnect({found_node_index, _selected_node_index});
				else if (_selected_node_index != found_node_index)
					connect({found_node_index, _selected_node_index});

				_selected_node_index = -1;
			}
		}
		else
			_selected_node_index = -1;
	}
	
}
