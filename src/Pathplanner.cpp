#include <Pathplanner.hpp>

Pathplanner::Pathplanner(std::function<bool(NodePtr, NodePtr)> compare_)
	: _compare{compare_}
	, _goal{nullptr}
{
}

Pathplanner::~Pathplanner()
{
}
