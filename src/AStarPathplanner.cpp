#include <AStarPathplanner.hpp>
#include <algorithm>
#include <Graph.hpp>

AStarPathplanner::AStarPathplanner(std::function<float(NodePtr, NodePtr, const Graph&)> heuristic_, const Graph& graph_)
	: Pathplanner{[this] (NodePtr topmost_, NodePtr newly_added_) -> bool
	{
		if (topmost_->value == newly_added_->value)
			return newly_added_ == _goal;
		return newly_added_->value < topmost_->value;
	}}
	, _heuristic{heuristic_}
	, _graph{graph_}
{
}

PathplanningReturnType AStarPathplanner::operator()(NodePtr start_, NodePtr goal_)
{ 
	_goal = goal_;

	_open = decltype(_open){_compare};

	PathplanningReturnType result;

	insert(start_);
	
	while (!_open.empty())
	{
		NodePtr current{_open.top()};
		_open.pop();
		current->tag = Closed;
		result.examined_nodes.push_back(current);

		if (current == goal_)
		{
			for (NodePtr trace{goal_}; trace != nullptr; trace = trace->parent)
				result.path.push_back(trace);

			std::reverse(result.path.begin(), result.path.end());

			return result;
		}

		for (auto successor : computeSuccessors(current))
		{
			auto evaluated{evaluate(successor, current)};
			float combined_value{evaluated.to_start_value + evaluated.heuristic_value};
			if ((successor->tag == New) != (combined_value < successor->value))
			{
				successor->parent = current;
				successor->to_start_value = evaluated.to_start_value;
				successor->heuristic_value = evaluated.heuristic_value;
				successor->value = combined_value;
				
				if (successor->tag != Open)
					insert(successor);
			}
		}
	}

	return result;  // No connection between Start and End nodes
}

void AStarPathplanner::insert(NodePtr node_)
{
	node_->tag = Open;
	_open.push(node_);
}

EvaluationReturnType AStarPathplanner::evaluate(NodePtr to_evaluate_, NodePtr based_on_) const
{
	EvaluationReturnType result;
	result.to_start_value = based_on_->to_start_value + getWeight(to_evaluate_, based_on_);
	result.heuristic_value = _heuristic(to_evaluate_, _goal, _graph);
	return result;
}
