#include <Graph.hpp>
#include <algorithm>
#include <math.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Gui/Consts.hpp>
#include <iostream>
#include <random>
#include <stack>
#include <unordered_set>

Graph::Graph(std::initializer_list<sf::Vector2i> node_positions_,
	std::initializer_list<std::pair<int, int>> node_indices_,
	float node_radius_)
{
	for (auto& node_position : node_positions_)
		_nodes.emplace_back(static_cast<sf::Vector2f>(node_position));

	for (auto& node_indices : node_indices_)
		connect(node_indices);
}

Graph::Graph(std::optional<int> seed_, float node_radius_)
	: _seed{seed_}
{
}

Graph::Graph(const Graph& other_)
	: _nodes{other_._nodes}
	, _selected_node_index{other_._selected_node_index}
	, _node_radius{other_._node_radius}
{
	for (auto& node : _nodes)
		for (auto& [neighbor, cost] : node.neighbors)
			const_cast<NodePtr&>(neighbor)._graph = this;
}

Graph& Graph::operator=(const Graph& other_)
{
	_nodes = other_._nodes;
	_selected_node_index = other_._selected_node_index;

	for (auto& node : _nodes)
		for (auto& [neighbor, cost] : node.neighbors)
			const_cast<NodePtr&>(neighbor)._graph = this;

	return *this;
}

void Graph::connect(std::pair<int, int> node_indices_)
{
	connect(operator[](node_indices_.first), operator[](node_indices_.second));
}

void Graph::disconnect(std::pair<int, int> node_indices_)
{
	disconnect(operator[](node_indices_.first), operator[](node_indices_.second));
}

void Graph::connect(NodePtr first_, NodePtr second_)
{
	sf::Vector2i delta{first_->position - second_->position};
	auto weight{std::hypot(delta.x, delta.y)};

	first_->neighbors[second_] = weight;
	second_->neighbors[first_] = weight;
}

void Graph::disconnect(NodePtr first_, NodePtr second_)
{
	second_->neighbors.erase(first_);
	first_->neighbors.erase(second_);
}

void Graph::modifyWeight(NodePtr first_, NodePtr second_, float new_weight_)
{
	// if (isinf(new_weight_))
	// {
	// 	disconnect(first_, second_);
	// 	return;
	// }

	if (first_->neighbors.find(second_) == first_->neighbors.end())
		connect(first_, second_);

	first_->neighbors[second_] = new_weight_;
	second_->neighbors[first_] = new_weight_;
}

NodePtr Graph::operator[](int index_)
{
	return {index_, *this}; 
}

void Graph::createNode(sf::Vector2f position_)
{
	_nodes.emplace_back(position_);
}

void Graph::deleteNode(int node_index_)
{
	_nodes.erase(_nodes.begin() + node_index_);
}

void Graph::resetNodes()
{
	for (auto& node : _nodes)
	{
		auto neighbors{std::move(node.neighbors)};
		auto position{node.position};
		auto visualization_parent{node.visualization_parent};
		node = {position};
		node.neighbors = neighbors;
		node.visualization_parent = visualization_parent;
	}
}

void Graph::draw(sf::RenderTarget& target_, sf::RenderStates states_) const
{
	using std::begin;
	using std::end;

	auto visualize_edge{[=] (const Node& first_, const Node& second_, sf::Color color_) -> sf::RectangleShape
	{
		sf::Vector2f distance{second_.position - first_.position};
		sf::RectangleShape visualized_edge{{std::hypot(distance.x, distance.y), .901f * _node_radius}};
		visualized_edge.setOrigin(0, .901f * _node_radius / 2);
		visualized_edge.setPosition(first_.position);
		visualized_edge.setFillColor(color_);
		visualized_edge.setRotation(std::atan(distance.y / distance.x) * 180u / 3.1415926f);

		if (distance.x < 0)
			visualized_edge.rotate(180);

		return visualized_edge;
	}};

	for (const auto& node : _nodes)
		for (const auto& [neighbor, cost] : node.neighbors)
			target_.draw(visualize_edge(node, *neighbor, {98, 100, 98}));

	{
		bool should_draw_path_edges{true};
		std::vector<sf::RectangleShape> path_edges;

		for (Node node : _nodes)
			if (node.visualization_status == Node::OnPath)
				for (auto [neighbor, cost] : node.neighbors)
					if (neighbor->visualization_status == Node::OnPath)
						path_edges.push_back(visualize_edge(node, *neighbor, {0, 0, 0}));

		if (should_draw_path_edges)
			for (auto& path_edge : path_edges)
				target_.draw(std::move(path_edge));
	}

	for (int node_index{0}; node_index < _nodes.size(); ++node_index)
	{
		sf::CircleShape visualized_node{_node_radius};
		visualized_node.setOrigin(_node_radius, _node_radius);
		visualized_node.setPosition(_nodes[node_index].position);
		
		if (node_index == _selected_node_index)
		{
			visualized_node.setOutlineThickness(-2.5f);
			visualized_node.setOutlineColor(sf::Color{186, 182, 96});
		}

		if (_nodes[node_index].visualization_status == Node::OnPath)
			visualized_node.setFillColor(sf::Color{39, 96, 122});
		else if (_nodes[node_index].visualization_status == Node::Examined)
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
			sf::Vector2f distance{static_cast<sf::Vector2f>(inputs_.cursor_position) - node_.position};
			return std::hypot(distance.x, distance.y) <= _node_radius;
		})};

		if (found != end(_nodes))
		{
			long long int found_node_index{found - begin(_nodes)};

			if (_selected_node_index == -1)
				_selected_node_index = found_node_index;
			else
			{
				if (!std::isinf(getWeight(operator[](_selected_node_index), operator[](found_node_index))))
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

void Graph::generateMaze()
{
	std::stack<NodePtr> stack;
	std::unordered_set<NodePtr> unvisited_nodes;
	Graph maze;

	std::mt19937 rng{std::random_device{}()};
	if (_seed)
		rng.seed(*_seed);

	for (int node_index = 0; node_index < _nodes.size(); ++node_index)
	{
		maze.createNode(_nodes[node_index].position);
		unvisited_nodes.insert(operator[](node_index));
	}

	auto mark_visited{[&] (NodePtr node_) -> NodePtr
	{
		unvisited_nodes.erase(unvisited_nodes.find(node_));
		return node_;
	}};

	auto is_unvisited{[&] (NodePtr node_)
	{
		return unvisited_nodes.find(node_) != unvisited_nodes.end();
	}};

	NodePtr current{mark_visited(operator[](0))};

	while (!unvisited_nodes.empty())
	{
		auto unvisited{(current->neighbors.size())};
		auto stacksize{stack.size()};
		std::vector<NodePtr> unvisited_neighbors;
		for (auto [neighbor, cost] : current->neighbors)
			if (is_unvisited(neighbor))
				unvisited_neighbors.push_back(neighbor);

		if (!unvisited_neighbors.empty())
		{
			std::uniform_int_distribution<int> random_unvisited_neighbor(0, unvisited_neighbors.size() - 1);
			auto chosen_neighbor{unvisited_neighbors[random_unvisited_neighbor(rng)]};

			stack.push(current);
			connect(maze[current.getIndex()], maze[chosen_neighbor.getIndex()]);
			current = mark_visited(chosen_neighbor);
		}
		else if (!stack.empty())
		{
			current = stack.top();
			stack.pop();
		}
	}

	*this = maze;
}
