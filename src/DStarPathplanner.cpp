#include <DStarPathplanner.hpp>
#include <iostream>
#include <Grid.hpp>

DStarPathplanner::DStarPathplanner(Graph& graph_)
	: Pathplanner{[this] (NodePtr topmost_, NodePtr newly_added_) -> bool
	{
		if (topmost_->key_value == newly_added_->key_value)
			return newly_added_ == _goal;
		return newly_added_->key_value < topmost_->key_value;
	}}
	, _map{graph_}
{
}

PathplanningReturnType DStarPathplanner::operator()(NodePtr start_, NodePtr goal_)
{
	_goal = goal_;
	_open = decltype(_open){_compare};

	_result = {};

	_open.push(goal_);

	while (!(_open.empty() || start_->tag == Closed))
		processState();

	for (NodePtr trace{start_}; trace != nullptr; trace = trace->parent)
		_result.path.push_back(trace);	

	return _result;
}

float DStarPathplanner::processState()
{
	NodePtr current{_open.top()};

	const float old_key_value{getMinimumKey()};

	_open.pop();
	current->tag = Closed;
	_result.examined_nodes.push_back(current);

	if (old_key_value == current->heuristic_value)
	{
		for (auto [neighbor_ref, cost] : current->neighbors)
		{
			auto neighbor{neighbor_ref};
			if (neighbor->tag == New ||
				(neighbor->parent == current && neighbor->heuristic_value != current->heuristic_value + cost) ||
				(neighbor->parent != current && neighbor->heuristic_value > current->heuristic_value + cost))
			{
				neighbor->parent = current;
				insert(neighbor, current->heuristic_value + cost);
			}
		}
	}
	else if (old_key_value < current->heuristic_value)
	{
		for (auto [neighbor, cost] : current->neighbors)
		{
			if (neighbor->heuristic_value <= old_key_value && current->heuristic_value > neighbor->heuristic_value + cost) 
			{
				current->parent = neighbor;
				current->heuristic_value = neighbor->heuristic_value + cost;
			}
		}
	}
	else
	{
		for (auto [neighbor_ref, cost] : current->neighbors)
		{
			auto neighbor{neighbor_ref};
			if (neighbor->tag == New ||
				 (neighbor->parent == current && neighbor->heuristic_value > current->heuristic_value + cost))
			{
				neighbor->parent = current;
				insert(neighbor, current->heuristic_value + cost);
			}
			else
			{
				if (neighbor->parent != current && neighbor->heuristic_value > current->heuristic_value + cost)
					insert(current, current->heuristic_value);
				else if (neighbor->parent != current && current->heuristic_value > neighbor->heuristic_value + cost &&
					neighbor->tag == Closed && neighbor->heuristic_value > old_key_value)
				{
					insert(neighbor, neighbor->heuristic_value);
				}
			}
		}
	}

	return getMinimumKey();
}

void DStarPathplanner::advance(int index_)
{
	if (index_ < _result.path.size() - 1)
	{

	}
};

float DStarPathplanner::modifyCost(NodePtr first_, NodePtr second_, float new_cost_)
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

void DStarPathplanner::insert(NodePtr node_, float new_heuristic_)
{

	switch (node_->tag)
	{	
		case New:
		node_->key_value = new_heuristic_;
		break;

		case Open:
		node_->key_value = std::min(node_->key_value, new_heuristic_);
		break;

		case Closed:
		node_->key_value = std::min(node_->heuristic_value, new_heuristic_);
		break;
	}

	node_->heuristic_value = new_heuristic_;

	if (node_->tag != Open)
	{
		node_->tag = Open;
		_open.push(node_);
	}
}
