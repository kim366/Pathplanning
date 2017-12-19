#include <DStarPathplanner.hpp>
#include <iostream>

DStarPathplanner::DStarPathplanner(Graph& graph_)
	: _map{graph_}
{
}

PathplanningReturnType DStarPathplanner::operator()(NodeHandle start_, NodeHandle goal_)
{
	_start = start_;
	_goal = goal_;

	_open.push(_goal);
	_goal->heuristic_value = 0;

	while (!(processState() == -1 || _start->tag == Closed));

	PathplanningReturnType result;
	for (NodeHandle trace{_start}; trace; trace = trace->parent)
		result.path.push_back(trace);

	return result;
}

float DStarPathplanner::processState()
{
	if (_open.empty())
		return -1;

	std::cout << _open.size() << '\n'; // Debug
	// std::cout << _start->getPathplanningData().tag << '\n'; // Debug

	NodeHandle current{_open.top()};

	float old_key_value{getMinimumKey()};

	_open.pop();
	current->tag = Closed;

	if (old_key_value < current->heuristic_value)
	{
			
		for (auto& [neighbor, cost] : current->neighbors)
		{
			if (neighbor->heuristic_value <= old_key_value && current->heuristic_value > neighbor->heuristic_value + cost) 
			{
				current->parent = neighbor;
				current->heuristic_value = neighbor->heuristic_value + cost;
			}
		}
	}
	else if (old_key_value == current->heuristic_value)
	{
		for (auto& [neighbor_ref, cost] : current->neighbors)
		{
			auto neighbor{neighbor_ref};
			if (neighbor->tag == New
				|| (neighbor->parent == current && neighbor->heuristic_value != current->heuristic_value + cost)
				|| (neighbor->parent != current && neighbor->heuristic_value > current->heuristic_value + cost))
			{
				neighbor->parent = current;
				insert(neighbor, current->heuristic_value + cost);
			}
		}
	}
	else
	{
		for (auto [neighbor, cost] : current->neighbors)
		{
			auto copy{neighbor};
			if (neighbor->tag == New
				|| (neighbor->parent == current && neighbor->heuristic_value > current->heuristic_value + cost))
			{
				copy->parent = current;
				insert(neighbor, current->heuristic_value + cost);
			}
			else
			{
				if (neighbor->parent && neighbor->heuristic_value > current->heuristic_value + cost)
				{
					insert(current, current->heuristic_value);
				}
				else if (neighbor->parent != current && current->heuristic_value > neighbor->heuristic_value + cost
					&& neighbor->tag == Closed
					&& neighbor->heuristic_value > old_key_value)
				{
					insert(neighbor, neighbor->heuristic_value);
				}
			}
		}
	}

	return getMinimumKey();
}

void handleCostDiscrepancy()
{
	
};

float DStarPathplanner::modifyCost(NodeHandle first_, NodeHandle second_, float new_cost_)
{
	_map.modifyWeight(first_, second_, new_cost_);

	if (first_->tag == Closed)
		insert(first_, first_->heuristic_value);

	return getMinimumKey();
}

float DStarPathplanner::getMinimumKey() const
{
	return _open.empty() ? -1 : _open.top()->key_value;
}

void DStarPathplanner::insert(NodeHandle node_, float new_heuristic_)
{
	auto& key_value{node_->key_value};

	switch (node_->tag)
	{	
		case New:
		key_value = new_heuristic_;
		break;

		case Open:
		key_value = std::min(node_->key_value, new_heuristic_);
		break;

		case Closed:
		key_value = std::min(node_->heuristic_value, new_heuristic_);
		break;
	}

	node_->heuristic_value = new_heuristic_;
	_open.push(node_);
}
