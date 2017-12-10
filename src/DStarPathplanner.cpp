#include <DStarPathplanner.hpp>

PathplanningReturnType DStarPathplanner::operator()(Node* start_, Node* goal_)
{

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
		key_value = std::min(node_->getPathplanningDataDStar({}).heuristic_value, new_heuristic_);
		break;
	}

	node_->getPathplanningDataDStar({}).heuristic_value = new_heuristic_;
	_open.push(node_);
}
