#include <algorithm>
#include <Graph.hpp>

template<typename H>
std::pair<std::optional<std::vector<const Node*>>, std::set<const Node*>>
	AStarPathplanner<H>::operator()(Graph& graph_, const Node* start_, const Node* end_)
{
	_start = start_;
	_end = end_;

	for (auto& node : graph_)
	{
		node->tag = New;
		node->parent = nullptr;
		node->value = 0.f;
	}
 
	while (!_open.empty())
		_open.pop();

	std::set<const Node*> examined_nodes;

	_open.push(const_cast<Node*>(start_));
	
	while (!_open.empty())
	{
		Node* current{_open.top()};
		_open.pop();
		current->tag = Closed;
		examined_nodes.insert(current);

		if (current == end_)
		{
			std::vector<const Node*> found_path;
			
			const Node* trace{current};
			while (trace)
			{
				found_path.push_back(trace);
				trace = trace->parent;
			}

			std::reverse(begin(found_path), end(found_path));

			return {{found_path}, examined_nodes};
		}

		auto successors{current->expand()};

		for (auto* successor : successors)
		{
			auto new_value{evaluate(successor, current)};
			float combined_value{new_value.first + new_value.second};
			if ((successor->tag == New) != (combined_value < successor->value))
			{
				successor->parent = current;
				successor->to_start_value = new_value.first;
				successor->heuristic_value = new_value.second;
				successor->value = combined_value;
				
				if (successor->tag != Open)
				{
					_open.push(successor);
					successor->tag = Open;
				}
			}
		}
	}

	return {{}, examined_nodes};  // No connection between Start and End nodes
}

template<typename H>
std::pair<float, float> AStarPathplanner<H>::evaluate(const Node* to_evaluate_, const Node* based_on_) const
{
	float to_start_value{based_on_->to_start_value + cost(to_evaluate_, based_on_)};
	float heuristic_value{_heuristic(to_evaluate_)};
	return {to_start_value, heuristic_value};
}