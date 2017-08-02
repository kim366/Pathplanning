#include <AStarPathplanner.hpp>

std::experimental::optional<std::pair<std::vector<const Node*>, unsigned>>
	AStarPathplanner::operator()(Node* start_, Node* end_)
{
	_start = start_;
	_end = end_;

	std::vector<const Node*> found_path;
	unsigned amount_of_expanded_nodes;

	_open.push(start_);
	
	while (!open.empty())
	{
		Node* current{open.top()};
		open.pop();
		current->tag = Node::Tag::Closed;

		if (current == end_)
		{
			Node* trace{current};
			while (trace.parent != nullptr)
			{
				found_path.push_back(trace);
				trace = trace.parent;
			}

			return std::experimental::make_optional(
			 	std::make_pair(found_path, amount_of_expanded_nodes));
		}

		auto successors{current->expand()};

		for (auto* successor : successors)
		{
			if (successor->tag == Node::Tag::New)
			{
				successor->parent = current;
				successor->value = evaluate(successor, current);
				_open.push(successor);
				successor->tag = Node::Tag::Open;
			}
			else if (float new_value{evaluate(successor, current)} < successor.value)
			{
				successor->parent = current;
				successor->value = new_value;
			}	

			if (successor->tag == Node::Tag::Closed)
			{
				for (auto* descendant : successor->expand())
				{
					if (float new_value{evaluate(descendant, successor)} < descendant.value)
					{
						descendant->parent = current;
						descendant->value = new_value;
					}
				}
			}
		}
	}

	return {};  // No connection between Start and End nodes
}

float AStarPathplanner::evaluate(const Node* to_evaluate_, const Node* based_on_)
{
}