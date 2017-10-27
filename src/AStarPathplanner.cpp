#include <AStarPathplanner.hpp>
#include <algorithm>
#include <Graph.hpp>

AStarPathplanner::AStarPathplanner(Graph& graph_, std::function<float(const Node*, HeuristicData)> heuristic_)
	: _graph(graph_)
	, _heuristic(heuristic_)
	, _heuristic_data{_graph, _goal}
{
}

PathplanningReturnType AStarPathplanner::operator()(const Node* start_, const Node* goal_)
{
	_start = start_;
	_goal = goal_;

	for (auto& node : _graph)
	{
		node->getPathplanningData({}).tag = New;
		node->getPathplanningData({}).parent = nullptr;
		node->getPathplanningData({}).value = 0.f;
	}
 
	while (!_open.empty())
		_open.pop();

	PathplanningReturnType result;

	_open.push(const_cast<Node*>(start_));
	
	while (!_open.empty())
	{
		Node* current{_open.top()};
		_open.pop();
		current->getPathplanningData({}).tag = Closed;
		result.examined_nodes.insert(current);

		if (current == goal_)
		{			
			const Node* trace{current};
			while (trace)
			{
				result.path.push_back(trace);
				trace = trace->getPathplanningData().parent;
			}

			std::reverse(begin(result.path), end(result.path));

			return result;
		}

		auto successors{current->expand()};

		for (auto* successor : successors)
		{
			auto [to_start_value, heuristic_value]{evaluate(successor, current)};
			float combined_value{to_start_value + heuristic_value};
			if ((successor->getPathplanningData().tag == New) != (combined_value < successor->getPathplanningData().value))
			{
				successor->getPathplanningData({}).parent = current;
				successor->getPathplanningData({}).to_start_value = to_start_value;
				successor->getPathplanningData({}).heuristic_value = heuristic_value;
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

std::pair<float, float> AStarPathplanner::evaluate(const Node* to_evaluate_, const Node* based_on_) const
{
	float to_start_value{based_on_->getPathplanningData().to_start_value + cost(to_evaluate_, based_on_)};
	float heuristic_value{_heuristic(to_evaluate_, _heuristic_data)};
	return {to_start_value, heuristic_value};
}