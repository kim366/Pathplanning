#include <Pathplanner.hpp>

Pathplanner::Pathplanner()
	: _compare{[this] (NodePtr topmost_, NodePtr newly_added_) -> bool
	{
		if (topmost_->key_value == newly_added_->key_value)
			return topmost_ != _goal;
		return newly_added_->key_value < topmost_->key_value;
	}}
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
