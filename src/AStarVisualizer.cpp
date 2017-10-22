#include <Gui/AStarVisualizer.hpp>
#include <Graph.hpp>

namespace Gui
{

AStarVisualizer::AStarVisualizer(Graph& graph_, const Node* start_, const Node* goal_)
	: _graph(graph_)
	, _start(start_)
	, _goal(goal_)
{
}

void AStarVisualizer::update(float delta_time_, const Inputs& inputs_)
{
	if (inputs_.event.released(sf::Keyboard::Space))
	{
		for (auto& expanded_node : _result.second)
			const_cast<Node*>(expanded_node)->status = Node::Standard;

		if (!_result.first.empty())
			for (auto& node_on_path : _result.first)
				const_cast<Node*>(node_on_path)->status = Node::Standard;
	
		_result = _find_shortest_path(_start, _goal);

		for (auto& expanded_node : _result.second)
			const_cast<Node*>(expanded_node)->status = Node::Expanded;

		if (!_result.first.empty())
			for (auto& node_on_path : _result.first)
				const_cast<Node*>(node_on_path)->status = Node::OnPath;
	}
	
}

} // namespace Gui
