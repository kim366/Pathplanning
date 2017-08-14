#include <iostream>
#include <Gui/AStarVisualizer.hpp>
#include <Graph.hpp>

namespace Gui
{

AStarVisualizer::AStarVisualizer(Graph& graph_, const Node* begin_, const Node* end_)
	: _begin(begin_)
	, _end(end_)
	, _graph(graph_)
{
}

void AStarVisualizer::update(float delta_time_, const Inputs& inputs_)
{
	if (inputs_.event.released(sf::Keyboard::Space))
	{
		if (_result.first)
			for (auto& node_on_path : *_result.first)
				const_cast<Node*>(node_on_path)->status = Node::Standard;
	
		_result = _find_shortest_path(_graph, _begin, _end);

		for (auto& expanded_node : _result.second)
			const_cast<Node*>(expanded_node)->status = Node::Expanded;

		if (_result.first)
			for (auto& node_on_path : *_result.first)
				const_cast<Node*>(node_on_path)->status = Node::OnPath;

		std::cout << _result.first->size() << ", " << _result.second.size() << '\n';
	}
	
}

} // namespace Gui