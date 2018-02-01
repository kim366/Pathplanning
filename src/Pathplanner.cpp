#include <Pathplanner.hpp>

Pathplanner::Pathplanner(std::function<bool(NodePtr, NodePtr)> compare_)
	: _compare{compare_}
	, _goal{nullptr}
{
}

Pathplanner::~Pathplanner()
{
}

void Pathplanner::resetOpen()
{
	_open = decltype(_open){_compare};
}

void Pathplanner::push(NodePtr node_)
{
	node_->tag = Open;
	_open.push(node_);
}

void Pathplanner::pop()
{
	auto top{_open.top()};
	top->tag = Closed;
	_open.pop();
}
