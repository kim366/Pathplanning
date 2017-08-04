#include <algorithm>

template<typename H>
std::experimental::optional<std::pair<std::vector<const Node*>, std::set<const Node*>>>
	AStarPathplanner<H>::operator()(const Node* start_, const Node* end_)
{
	_start = start_;
	_end = end_;

	std::vector<const Node*> found_path;
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
			const Node* trace{current};
			while (trace)
			{
				found_path.push_back(trace);
				trace = trace->parent;
			}

			std::reverse(begin(found_path), end(found_path));

			return std::experimental::make_optional(
			 	std::make_pair(found_path, examined_nodes));
		}

		auto successors{current->expand()};

		for (auto* successor : successors)
		{
			float new_value{evaluate(successor, current)};
			if ((successor->tag == New) != (new_value < successor->value))
			{
				successor->parent = current;
				successor->value = new_value;
				
				if (successor->tag != Open)
				{
					_open.push(successor);
					successor->tag = Open;
				}
			}
		}
	}

	return {};  // No connection between Start and End nodes
}

template<typename H>
float AStarPathplanner<H>::evaluate(const Node* to_evaluate_, const Node* based_on_) const
{
	float to_start_value{based_on_->value + cost(to_evaluate_, based_on_)};
	float heuristic_value{_heuristic(to_evaluate_)};
	return to_start_value + heuristic_value;
}