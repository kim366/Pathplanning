#include <Gui/PathplannerVisualizer.hpp>
#include <Graph.hpp>
#include <iostream>

namespace Gui
{

PathplannerVisualizer::PathplannerVisualizer(std::unique_ptr<Pathplanner>&& pathplanner_, Graph& graph_, NodePtr start_, NodePtr goal_)
	: _pathplanner{std::move(pathplanner_)}
	, _graph{graph_}
	, _start{start_}
	, _goal{goal_}
	, _map{graph_}
{
}

void PathplannerVisualizer::update(float delta_time_, const Inputs& inputs_)
{
	if (inputs_.event.pressed(sf::Keyboard::Space))
	{
		_graph.resetNodes();

		bool uninformed{false};

#ifdef UNINFORMED		
		if (!(uninformed = !dynamic_cast<DStarPathplanner*>(_pathplanner.get())))
			_pathplanner = std::make_unique<DStarPathplanner>(_map);
#endif

		auto& find_shortest_path{*_pathplanner};
		PathplanningReturnType result;
		if (uninformed)
			result = find_shortest_path(_map[_start.getIndex()], _map[_goal.getIndex()]);
		else
			result = find_shortest_path(_start, _goal);

		if (uninformed)
		{
			for (int node_index{0}; node_index < result.path.size(); ++node_index)
			{
				NodePtr node{result.path[node_index]};

				_graph[node.getIndex()]->parent = node->parent;

				if (node_index + 1 < result.path.size())
				{
					NodePtr next_node{result.path[node_index + 1]};
					_graph[node.getIndex()]->child = _graph[next_node.getIndex()];
					node->child = next_node;
				}
			}

			auto dynamic_path{result.path};
			result.path.clear();

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
						result.examined_nodes.insert(result.examined_nodes.end(), dynamic_result.examined_nodes.begin(), dynamic_result.examined_nodes.end());

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

				result.path.push_back(node);
			}
		}
		
		for (auto examined_node : result.examined_nodes)
			_graph[examined_node.getIndex()]->visualization_status = Node::Examined;

		for (auto node_on_path : result.path)
			_graph[node_on_path.getIndex()]->visualization_status = Node::OnPath;

		float sum{0};
		for (int node_index{0}; node_index + 1 < result.path.size(); ++node_index)
		{
			NodePtr node{result.path[node_index]}, next_node{result.path[node_index + 1]};
			sf::Vector2i delta{node->position - next_node->position};
			sum += std::hypot(delta.x, delta.y);
		}
		std::cout << "Path length: " << sum << "; " << result.examined_nodes.size() << " Nodes Examined\n";

		find_shortest_path.resetOpen();

		if (DStarPathplanner* dstar_find_shortest_path{dynamic_cast<DStarPathplanner*>(_pathplanner.get())}; dstar_find_shortest_path)
			dstar_find_shortest_path->resetResult();
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
