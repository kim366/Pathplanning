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

		if (dynamic_cast<DStarPathplanner*>(_pathplanner.get()))
			_pathplanner = std::make_unique<DStarPathplanner>(_map);

		auto& find_shortest_path{*_pathplanner};
		auto result{find_shortest_path(_start, _goal)};

		for (auto examined_node : result.examined_nodes)
			_graph[examined_node.getIndex()]->visualization_status = Node::Examined;

		for (auto node_on_path : result.path)
		{
			_graph[node_on_path.getIndex()]->visualization_status = Node::OnPath;
			_graph[node_on_path.getIndex()]->parent = node_on_path->parent;
		}

		std::cout << result.path.back()->value << '\n';
		
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
