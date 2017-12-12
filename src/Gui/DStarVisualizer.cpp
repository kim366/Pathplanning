#include <Gui/DStarVisualizer.hpp>
#include <Graph.hpp>
#include <iostream>

namespace Gui
{

DStarVisualizer::DStarVisualizer(Graph& graph_, int start_, int goal_)
	: _graph{graph_}
	, _start{start_}
	, _goal{goal_}
{
}

void DStarVisualizer::update(float delta_time_, const Inputs& inputs_)
{
	if (inputs_.event.pressed(sf::Keyboard::Space))
	{
		for (auto& examined_node : _result.examined_nodes)
			examined_node->getVisualization({}).status = NodeComponents::Visualization::Standard;

		for (auto& node_on_path : _result.path)
			node_on_path->getVisualization({}).status = NodeComponents::Visualization::Standard;
	
		_result = _find_shortest_path(_start, _goal);

		for (auto& examined_node : _result.examined_nodes)
			examined_node->getVisualization({}).status = NodeComponents::Visualization::Examined;

		for (auto& node_on_path : _result.path)
			node_on_path->getVisualization({}).status = NodeComponents::Visualization::OnPath;

	}
}

} // namespace Gui
