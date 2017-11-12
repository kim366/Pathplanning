#include <AStarPathplanner.hpp>
#include <algorithm>
#include <Graph.hpp>

AStarPathplanner::AStarPathplanner(Graph& graph_, std::function<float(const Node*, HeuristicData)> heuristic_)
	: _graph{graph_}
	, _heuristic{heuristic_}
	, _heuristic_data{_graph, _goal}
{
}

PathplanningReturnType AStarPathplanner::operator()(Node* start_, Node* goal_)
{
	_start = start_;
	_goal = goal_;

	for (auto& node : _graph)
		node->getPathplanningData({}) = {};
 
	_open = decltype(_open){_compare};

	PathplanningReturnType result;

	_open.push(start_);
	
	while (!_open.empty())
	{
		Node* current{_open.top()};
		_open.pop();
		current->getPathplanningData({}).tag = Closed;
		result.examined_nodes.insert(current);

		if (current == goal_)
		{			
			Node* trace{current};
			while (trace)
			{
				result.path.push_back(trace);
				trace = trace->getPathplanningData({}).parent;
			}

			std::reverse(begin(result.path), end(result.path));

			return result;
		}

		auto successors{computeSuccessors(current, {})};

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
	result.to_start_value = based_on_->getPathplanningData().to_start_value + getWeight(to_evaluate_, based_on_);
	result.heuristic_value = _heuristic(to_evaluate_, _heuristic_data);
	return result;
}