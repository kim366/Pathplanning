#include <DStarPathplanner.hpp>
#include <iostream>
#include <Grid.hpp>

DStarPathplanner::DStarPathplanner(Graph& graph_)
	: _map{graph_}
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

	if (old_key_value == current->value)
	{
		for (auto [neighbor_ref, cost] : current->neighbors)
		{
			auto neighbor{neighbor_ref};
			if (neighbor->tag == New ||
				(neighbor->parent == current && neighbor->value != current->value + cost) ||
				(neighbor->parent != current && neighbor->value > current->value + cost))
			{
				neighbor->parent = current;
				insert(neighbor, current->value + cost);
			}
		}
	}
	else if (old_key_value < current->value)
	{
		for (auto [neighbor, cost] : current->neighbors)
		{
			if (neighbor->value <= old_key_value && current->value > neighbor->value + cost) 
			{
				current->parent = neighbor;
				current->value = neighbor->value + cost;
			}
		}
	}
	else
	{
		for (auto [neighbor_ref, cost] : current->neighbors)
		{
			auto neighbor{neighbor_ref};
			if (neighbor->tag == New ||
				 (neighbor->parent == current && neighbor->value > current->value + cost))
			{
				neighbor->parent = current;
				insert(neighbor, current->value + cost);
			}
			else
			{
				if (neighbor->parent != current && neighbor->value > current->value + cost)
					insert(current, current->value);
				else if (neighbor->parent != current && current->value > neighbor->value + cost &&
					neighbor->tag == Closed && neighbor->value > old_key_value)
				{
					insert(neighbor, neighbor->value);
				}
			}
		}
	}

	return getMinimumKey();
}

void handleCostDiscrepancy()
{
	
};

float DStarPathplanner::modifyCost(NodePtr first_, NodePtr second_, float new_cost_)
{
	_map.modifyWeight(first_, second_, new_cost_);

	if (first_->tag == Closed)
		insert(first_, first_->value);

	return getMinimumKey();
}

float DStarPathplanner::getMinimumKey() const
{
	return _open.empty() ? -1 : _open.top()->key_value;
}

void DStarPathplanner::insert(NodePtr node_, float new_value_)
{

	switch (node_->tag)
	{	
		case New:
		node_->key_value = new_value_;
		break;

		case Open:
		node_->key_value = std::min(node_->key_value, new_value_);
		break;

		case Closed:
		node_->key_value = std::min(node_->value, new_value_);
		break;
	}

	node_->value = new_value_;

	if (node_->tag != Open)
	{
		node_->tag = Open;
		_open.push(node_);
	}
}
