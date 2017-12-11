#include <DStarPathplanner.hpp>

PathplanningReturnType DStarPathplanner::operator()(Node* start_, Node* goal_)
{
	while (!(processState() == -1 || goal_->getPathplanningData().tag == Closed));

	PathplanningReturnType result;
	for (Node* trace{start_}; trace != nullptr; trace = trace->getPathplanningData({}).parent)
		result.path.push_back(trace);

	return result;
}

float DStarPathplanner::processState()
{
	if (_open.empty())
		return -1;

	Node* current{_open.top()};

	float old_key_value{getMinimumKey()};
	_open.pop();

	const float current_heuristic_value{current->getPathplanningData({}).heuristic_value};

	if (old_key_value < current_heuristic_value)
	{
		for (auto& [neighbor, cost] : current->getData().connections)
		{
			if (neighbor->getPathplanningData().heuristic_value <= old_key_value && current_heuristic_value > current->getPathplanningData().heuristic_value + cost) 
			{
				current->getPathplanningData({}).parent = neighbor;
				current->getPathplanningData({}).heuristic_value = current->getPathplanningData().heuristic_value + cost;
			}
		}
	}
	else if (old_key_value == current_heuristic_value)
	{
		for (auto& [neighbor, cost] : current->getData().connections)
		{
			const float new_heuristic_value{current->getPathplanningData({}).heuristic_value + getWeight(neighbor, current)};

			if (neighbor->getPathplanningData().tag == New
				|| (neighbor->getPathplanningData().parent == current && neighbor->getPathplanningData().heuristic_value != current->getPathplanningData().heuristic_value + cost)
				|| (neighbor->getPathplanningData().parent != current && neighbor->getPathplanningData().heuristic_value > current->getPathplanningData().heuristic_value + cost))
			{
				neighbor->getPathplanningData({}).parent = current;
				insert(neighbor, current->getPathplanningData().heuristic_value + cost);
			}
		}
	}
	else
	{
		for (auto& [neighbor, cost] : current->getData().connections)
		{
			if (neighbor->getPathplanningData().tag == New
				|| (neighbor->getPathplanningData().parent == current && neighbor->getPathplanningData().heuristic_value > current->getPathplanningData().heuristic_value + cost))
			{
				neighbor->getPathplanningData({}).parent = current;
				insert(neighbor, current->getPathplanningData().heuristic_value + cost);
			}
			else
			{
				if (neighbor->getPathplanningData().parent && neighbor->getPathplanningData().heuristic_value > current->getPathplanningData().heuristic_value + cost)
				{
					insert(current, current->getPathplanningData().heuristic_value);
				}
				else if (neighbor->getPathplanningData().parent != current && current->getPathplanningData().heuristic_value > current->getPathplanningData().heuristic_value + cost
					&& neighbor->getPathplanningData().tag == Closed
					&& current->getPathplanningData().heuristic_value)
				{
					insert(neighbor, neighbor->getPathplanningData().heuristic_value);
				}
			}
		}
	}

	return getMinimumKey();
}

float modifyCost(Node* node1_, Node* node2_, float new_cost)
{
	 = new_cost;

	if (node1_->getPathplanningData().tag == Closed)
		insert(node1_, node1_->getPathplanningData().heuristic_value);

	return getMinimumKey();
}

float DStarPathplanner::getMinimumKey() const
{
	return _open.empty() ? -1 : _open.top()->getDStarData().key_value;
}

void DStarPathplanner::insert(Node* node_, float new_heuristic_)
{
	auto& key_value{node_->getDStarData({}).key_value};

	switch (node_->getPathplanningData().tag)
	{	
		case New:
		key_value = new_heuristic_;
		break;

		case Open:
		key_value = std::min(node_->getDStarData().key_value, new_heuristic_);
		break;

		case Closed:
		key_value = std::min(node_->getPathplanningData({}).heuristic_value, new_heuristic_);
		break;
	}

	node_->getPathplanningData({}).heuristic_value = new_heuristic_;
	_open.push(node_);
}
