#include <Gui/PathplannerVisualizer.hpp>
#include <Graph.hpp>
#include <iostream>

namespace Gui
{

PathplannerVisualizer::PathplannerVisualizer(std::unique_ptr<Pathplanner>&& pathplanner_, Graph& graph_, NodeHandle start_, NodeHandle goal_)
	: _pathplanner{std::move(pathplanner_)}
	, _graph{graph_}
	, _start{start_}
	, _goal{goal_}
{
}

void PathplannerVisualizer::update(float delta_time_, const Inputs& inputs_)
{
	if (inputs_.event.pressed(sf::Keyboard::Space))
	{
		_graph.resetNodes();

		auto& find_shortest_path{*_pathplanner};
		auto result{find_shortest_path(_start, _goal)};

		for (auto& examined_node : result.examined_nodes)
			examined_node->visualization_status = Node::Examined;

		for (auto& node_on_path : result.path)
			node_on_path->visualization_status = Node::OnPath;

		// std::cout << result.path.back()->value << '\n';
	}

	if (inputs_.event.pressed(sf::Keyboard::D))
		_pathplanner = std::make_unique<DStarPathplanner>(_graph);

	if (inputs_.event.pressed(sf::Keyboard::N))
		_pathplanner = std::make_unique<AStarPathplanner>(None{}, _graph);

	if (inputs_.event.pressed(sf::Keyboard::M))
		_pathplanner = std::make_unique<AStarPathplanner>(Manhattan{}, _graph);

	if (inputs_.event.pressed(sf::Keyboard::O))
		_pathplanner = std::make_unique<AStarPathplanner>(Octile{}, _graph);

	if (inputs_.event.pressed(sf::Keyboard::E))
		_pathplanner = std::make_unique<AStarPathplanner>(Euclidean{}, _graph);

}

} // namespace Gui
