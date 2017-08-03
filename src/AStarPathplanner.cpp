#include <AStarPathplanner.hpp>
#include <algorithm>

std::experimental::optional<std::pair<std::vector<const Node*>, unsigned>>
	AStarPathplanner::operator()(const Node* start_, const Node* end_)
{
	_start = start_;
	_end = end_;

	std::vector<const Node*> found_path;
	auto amount_of_examined_nodes{0u};

	_open.push(const_cast<Node*>(start_));
	
	while (!_open.empty())
	{
		Node* current{_open.top()};
		_open.pop();
		current->tag = Node::Tag::Closed;

		if (current == end_)
		{
			++amount_of_examined_nodes;

			const Node* trace{current};
			while (trace)
			{
				found_path.push_back(trace);
				trace = trace->parent;
			}

			std::reverse(begin(found_path), end(found_path));

			return std::experimental::make_optional(
			 	std::make_pair(found_path, amount_of_examined_nodes));
		}

		auto successors{current->expand()};

		for (auto* successor : successors)
		{
			float new_value{evaluate(successor, current)};
			if (successor->tag == Node::Tag::New)
				++amount_of_examined_nodes;

			if ((successor->tag == Node::Tag::New) != (new_value < successor->value))
			{
				successor->parent = current;
				successor->value = new_value;
				_open.push(successor);
				successor->tag = Node::Tag::Open;
			}
		}
	}

	return {};  // No connection between Start and End nodes
}

float AStarPathplanner::evaluate(Node* to_evaluate_, Node* based_on_)
{
}