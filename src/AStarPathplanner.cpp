#include <AStarPathplanner.hpp>
#include <algorithm>
#include <Graph.hpp>

AStarPathplanner::AStarPathplanner(Graph& graph_, std::function<float(const Node*, HeuristicData)> heuristic_)
	: _graph(graph_)
	, _heuristic(heuristic_)
	, _heuristic_data{_graph, _goal}
{
}

std::pair<std::vector<const Node*>, std::set<const Node*>>
	AStarPathplanner::operator()(const Node* start_, const Node* goal_)
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

	std::set<const Node*> examined_nodes;

	_open.push(const_cast<Node*>(start_));
	
	while (!_open.empty())
	{
		Node* current{_open.top()};
		_open.pop();
		current->getPathplanningData({}).tag = Closed;
		examined_nodes.insert(current);

		if (current == goal_)
		{
			std::vector<const Node*> found_path;
			
			const Node* trace{current};
			while (trace)
			{
				found_path.push_back(trace);
				trace = trace->getPathplanningData().parent;
			}

			std::reverse(begin(found_path), end(found_path));

			return {{found_path}, examined_nodes};
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

	return {{}, examined_nodes};  // No connection between Start and End nodes
}

std::pair<float, float> AStarPathplanner::evaluate(const Node* to_evaluate_, const Node* based_on_) const
{
	float to_start_value{based_on_->getPathplanningData().to_start_value + cost(to_evaluate_, based_on_)};
	float heuristic_value{_heuristic(to_evaluate_, _heuristic_data)};
	return {to_start_value, heuristic_value};
}