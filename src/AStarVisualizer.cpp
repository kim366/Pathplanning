#include <Gui/AStarVisualizer.hpp>
#include <Graph.hpp>

namespace Gui
{

AStarVisualizer::AStarVisualizer(Graph& graph_, Node* start_, Node* goal_)
	: _graph{graph_}
	, _start{start_}
	, _goal{goal_}
{
}

void AStarVisualizer::update(float delta_time_, const Inputs& inputs_)
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
