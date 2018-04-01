#include <Gui/PathplannerVisualizer.hpp>
#include <Graph.hpp>
#include <iostream>

namespace Gui
{

PathplannerVisualizer::PathplannerVisualizer(std::unique_ptr<Pathplanner>&& pathplanner_, Graph& graph_, NodePtr start_, NodePtr goal_, bool uninformed_, bool immediately_, bool animate_)
	: _pathplanner{std::move(pathplanner_)}
	, _graph{graph_}
	, _start{start_}
	, _goal{goal_}
	, _map{graph_}
	, _uninformed{uninformed_}
	, _immediately{immediately_}
	, _immediate_done{false}
	, _initial_path_generated{false}
	, _animate{animate_}
{
}

void PathplannerVisualizer::update(float delta_time_, const Inputs& inputs_)
{
	auto& find_shortest_path{*_pathplanner};

	if (inputs_.event.pressed(sf::Keyboard::Space) || (_immediately && !_immediate_done))
	{
		_initial_path_generated = true;
		_immediate_done = true;

		_graph.resetNodes();

		bool actual_uninformed{false};

		if (_uninformed)
		{
			if (!(actual_uninformed = !dynamic_cast<DStarPathplanner*>(_pathplanner.get())))
				_pathplanner = std::make_unique<DStarPathplanner>(_map);
		}
		else
		{
			_map = _graph;
			if (dynamic_cast<DStarPathplanner*>(_pathplanner.get()))
				_pathplanner = std::make_unique<DStarPathplanner>(_map);
		}


		if (actual_uninformed)
			_result = find_shortest_path(_map[_start.getIndex()], _map[_goal.getIndex()]);
		else
			_result = find_shortest_path(_start, _goal);

		if (actual_uninformed)
		{
			for (int node_index{0}; node_index < _result.path.size(); ++node_index)
			{
				NodePtr node{_result.path[node_index]};

				_graph[node.getIndex()]->parent = node->parent;

				if (node_index + 1 < _result.path.size())
				{
					NodePtr next_node{_result.path[node_index + 1]};
					_graph[node.getIndex()]->child = _graph[next_node.getIndex()];
					node->child = next_node;
				}
			}

			auto dynamic_path{_result.path};
			_result.path.clear();

			for (NodePtr node{dynamic_path.front()}; !dynamic_path.empty(); node = dynamic_path.front())
			{
				dynamic_path.erase(dynamic_path.begin());

				if (node->child != nullptr)
				{
					const float new_weight{getWeight(_graph[node.getIndex()], _graph[node->child.getIndex()])};
					
					if (getWeight(node, node->child) != new_weight)
					{
						find_shortest_path.resetOpen();

						for (const auto [neighbor, cost] : node->neighbors)
							_map.modifyWeight(node, neighbor, getWeight(_graph[node.getIndex()], _graph[neighbor.getIndex()]));

						_map.resetNodes();
						auto dynamic_result{find_shortest_path(node, _map[_goal.getIndex()])};
						dynamic_path = std::move(dynamic_result.path);
						_result.examined_nodes.insert(_result.examined_nodes.end(), dynamic_result.examined_nodes.begin(), dynamic_result.examined_nodes.end());

						for (int node_index{0}; node_index < dynamic_path.size(); ++node_index)
						{
							NodePtr node{dynamic_path[node_index]};

							_graph[node.getIndex()]->parent = node->parent;

							if (node_index + 1 < dynamic_path.size())
							{
								NodePtr next_node{dynamic_path[node_index + 1]};
								_graph[node.getIndex()]->child = _graph[next_node.getIndex()];
								node->child = next_node;
							}
						}
					}
				}

				_result.path.push_back(node);
			}
		}
		
		for (auto examined_node : _result.examined_nodes)
			_graph[examined_node.getIndex()]->visualization_status = Node::Examined;

		for (auto node_on_path : _result.path)
			_graph[node_on_path.getIndex()]->visualization_status = Node::OnPath;

		float sum{0};
		for (int node_index{0}; node_index + 1 < _result.path.size(); ++node_index)
		{
			NodePtr node{_result.path[node_index]}, next_node{_result.path[node_index + 1]};
			sf::Vector2i delta{node->position - next_node->position};
			sum += std::hypot(delta.x, delta.y);
		}
		std::cout << "Path length: " << sum << "; " << _result.examined_nodes.size() << " Nodes Examined\n";

		find_shortest_path.resetOpen();

		if (DStarPathplanner* dstar_find_shortest_path{dynamic_cast<DStarPathplanner*>(_pathplanner.get())}; dstar_find_shortest_path)
			dstar_find_shortest_path->resetResult();

	}

	if (_initial_path_generated && _animate)
	{
		if (!_result.examined_nodes.empty())
		{
			_pathplanner = std::make_unique<AStarPathplanner>(Euclidean{});
			auto& find_shortest_path{*_pathplanner};
			_graph.resetNodes();
			for (auto& node : _graph._nodes)
				node.visualization_status = Node::Standard;

			for (auto& node : _animated_examined_nodes)
				node->visualization_status = Node::Examined;

			auto current_animated_result{find_shortest_path(_graph[_start.getIndex()], _graph[_result.examined_nodes.front().getIndex()])};
			_animated_examined_nodes.push_back(_graph[_result.examined_nodes.front().getIndex()]);
			_result.examined_nodes.erase(_result.examined_nodes.begin());

			for (auto node : current_animated_result.path)
				_graph[node.getIndex()]->visualization_status = Node::OnPath;			
		}
	}

	if (inputs_.event.pressed(sf::Keyboard::D))
		_pathplanner = std::make_unique<DStarPathplanner>(_map);

	if (inputs_.event.pressed(sf::Keyboard::N))
		_pathplanner = std::make_unique<AStarPathplanner>([] (...) { return 0; });

	if (inputs_.event.pressed(sf::Keyboard::M))
		_pathplanner = std::make_unique<AStarPathplanner>(Manhattan{});

	if (inputs_.event.pressed(sf::Keyboard::O))
		_pathplanner = std::make_unique<AStarPathplanner>(Octile{});

	if (inputs_.event.pressed(sf::Keyboard::E))
		_pathplanner = std::make_unique<AStarPathplanner>(Euclidean{});

}

} // namespace Gui
