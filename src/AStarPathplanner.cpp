#include <AStarPathplanner.hpp>
#include <algorithm>
#include <Graph.hpp>

AStarPathplanner::AStarPathplanner(Graph& graph_, std::function<float(const Node*, HeuristicData)> heuristic_)
	: _graph{graph_}
	, _heuristic{heuristic_}
	, _heuristic_data{_graph, _goal}
{
}

PathplanningReturnType AStarPathplanner::operator()(int start_index_, int goal_index_)
{
	_start = &_graph.getNode(start_index_);
	_goal = &_graph.getNode(goal_index_);

	for (auto& node : _graph)
		node.getPathplanningData({}) = {};
 
	_open = decltype(_open){_compare};

	PathplanningReturnType result;

	_open.push(_start);
	
	while (!_open.empty())
	{
		Node* current{_open.top()};
		_open.pop();
		current->getPathplanningData({}).tag = Closed;
		result.examined_nodes.insert(current);

		if (current == _goal)
		{
			for (Node* trace{current}; trace != nullptr; trace = trace->getPathplanningData({}).parent)
				result.path.push_back(trace);

			std::reverse(begin(result.path), end(result.path));

			return result;
		}

		auto successors{computeSuccessors(_graph, current, {})};

		for (auto successor : successors)
		{
			auto evaluated{evaluate(successor, current)};
			float combined_value{evaluated.to_start_value + evaluated.heuristic_value};
			if ((successor->getPathplanningData().tag == New) != (combined_value < successor->getPathplanningData().value))
			{
				successor->getPathplanningData({}).parent = current;
				successor->getPathplanningData({}).to_start_value = evaluated.to_start_value;
				successor->getPathplanningData({}).heuristic_value = evaluated.heuristic_value;
				successor->getPathplanningData({}).value = combined_value;
				
				if (successor->getPathplanningData().tag != Open)
				{
					_open.push(successor);
					successor->getPathplanningData({}).tag = Open;
				}
			}
		}
	}

	return result;  // No connection between Start and End nodes
}

EvaluationReturnType AStarPathplanner::evaluate(const Node* to_evaluate_, const Node* based_on_) const
{
	EvaluationReturnType result;
	result.to_start_value = based_on_->getPathplanningData().to_start_value + getWeight(_graph, *to_evaluate_, *based_on_);
	result.heuristic_value = _heuristic(to_evaluate_, _heuristic_data);
	return result;
}