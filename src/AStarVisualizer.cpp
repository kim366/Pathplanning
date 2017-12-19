#include <Gui/AStarVisualizer.hpp>
#include <Graph.hpp>
#include <iostream>

namespace Gui
{

AStarVisualizer::AStarVisualizer(Graph& graph_, NodeHandle start_, NodeHandle goal_)
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
			examined_node->visualization_status = Node::Standard;

		for (auto& node_on_path : _result.path)
			node_on_path->visualization_status = Node::Standard;
	
		_graph.resetNodes();
		_result = _find_shortest_path(_start, _goal);

		for (auto& examined_node : _result.examined_nodes)
			examined_node->visualization_status = Node::Examined;

		for (auto& node_on_path : _result.path)
			node_on_path->visualization_status = Node::OnPath;

		float sum1 = _result.path.back()->value, sum2 = 0;
		
		for (int i{0}; i < _result.path.size() - 1; ++i)
			sum2 += getWeight(_result.path[i], _result.path[i + 1]);

		std::cout << sum2 << ", " << sum2 << '\n';

		// std::cout << sum1 << ", " << sum2 << ", " << dynamic_cast<Grid&>(_graph).diagonal_unit << ", " << getWeight(_result.path[0], _result.path[1]) << "Not Equal!!!!"/*<< ", " << _result.path.size()*/;
	}
	
}

} // namespace Gui
