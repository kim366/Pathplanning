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
	if (inputs_.event.released(sf::Keyboard::Space)) // TODO: released -> pressed
	{
		for (auto& expanded_node : _examined_nodes) // TODO: expanded -> examined
			const_cast<Node*>(expanded_node)->status = Node::Standard;

		for (auto& node_on_path : _found_path)
			const_cast<Node*>(node_on_path)->status = Node::Standard;
	
		auto result = _find_shortest_path(_start, _goal);
		_found_path = result.first;
		_examined_nodes = result.second;

		for (auto& expanded_node : _examined_nodes)
			const_cast<Node*>(expanded_node)->status = Node::Expanded;

		for (auto& node_on_path : _found_path)
			const_cast<Node*>(node_on_path)->status = Node::OnPath;
	}
	
}

} // namespace Gui
