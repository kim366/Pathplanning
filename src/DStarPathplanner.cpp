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
	auto& updated_graph{start_.getGraph()};
	_map.resetNodes();
	NodePtr start{_map[start_.getIndex()]};
	_goal = _map[goal_.getIndex()];
	_open = decltype(_open){_compare};
	_result = {};

	_open.push(_goal);

	while (!(processState() == -1 || start->tag == Closed));

	for (NodePtr trace{start}; trace != nullptr; trace = trace->parent)
	{
		float new_weight{getWeight(updated_graph[trace.getIndex()], updated_graph[trace->parent.getIndex()])};
		if (getWeight(trace, trace->parent) != new_weight)
		{
			modifyCost(trace, trace->parent, new_weight);
			trace->heuristic_value = std::numeric_limits<float>::infinity();
			while (!(processState() >= trace->heuristic_value));
		}

		_result.path.push_back(trace);
	}

	return _result;
}

float DStarPathplanner::processState()
{
	if (_open.empty())
		return -1;

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

bool DStarPathplanner::advance(int index_)
{
	NodePtr current{_result.path[index_]};
	NodePtr next{_result.path[index_ + 1]};

	float new_weight{getWeight(current, next)};
	float old_weight{getWeight(_map[current.getIndex()], _map[next.getIndex()])};

	// Goal not reached
	if (index_ < _result.path.size() - 1 && new_weight != old_weight)
	{
		modifyCost(current, next, new_weight);
		return true;
	}

	return false;
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
