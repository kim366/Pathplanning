#include <DStarPathplanner.hpp>
#include <cmath>
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
		if (trace->parent != nullptr)
		{
			float new_weight{getWeight(updated_graph[trace.getIndex()], updated_graph[trace->parent.getIndex()])};
			
			if (getWeight(trace, trace->parent) != new_weight)
			{
				for (const auto [neighbor, cost] : trace->neighbors)
				{
					const auto updated_neighbor{updated_graph[neighbor.getIndex()]};

					modifyCost(trace, neighbor, getWeight(updated_graph[trace.getIndex()], updated_neighbor));
				}

				trace->heuristic_value = std::numeric_limits<float>::infinity();
				while (!(processState() >= trace->heuristic_value));
			}
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

	if (std::find(_result.examined_nodes.begin(), _result.examined_nodes.end(), current) == _result.examined_nodes.end())
		_result.examined_nodes.push_back(current);

	current->tag = Closed;

	if (current->heuristic_value == old_key_value)
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
	else if (current->heuristic_value > old_key_value)
	{
		for (auto [neighbor_ref, cost] : current->neighbors)
		{
			auto neighbor{neighbor_ref};
			if (current->heuristic_value > neighbor->heuristic_value + cost) 
			{
				current->parent = neighbor;
				current->heuristic_value = neighbor->heuristic_value + cost;
			}
		}
	}

	return getMinimumKey();
}

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
