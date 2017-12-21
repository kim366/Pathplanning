#include <NodeHandle.hpp>
#include <Graph.hpp>

NodeHandle::NodeHandle(std::nullptr_t)
	: _index{-1}
	, _graph{nullptr}
{
}

NodeHandle::NodeHandle(int index_, Graph& graph_)
	: _index{index_}
	, _graph{&graph_}
{
}

Node* NodeHandle::operator->()
{
	return &_graph->_nodes[_index];
}

const Node* NodeHandle::operator->() const
{
	return &_graph->_nodes[_index];
}

Node& NodeHandle::operator*()
{
	return _graph->_nodes[_index];
}

const Node& NodeHandle::operator*() const
{
	return _graph->_nodes[_index];
}

bool NodeHandle::operator==(NodeHandle other_) const
{
	return _index == other_._index && _graph == other_._graph;
}

bool NodeHandle::operator!=(NodeHandle other_) const
{
	return !(*this == other_);
}

// bool NodeHandle::operator==(Node* other_) const
// {
// 	return &**this == other_;
// }

// bool NodeHandle::operator!=(Node* other_) const
// {
// 	return !(*this == other_);
// }

bool NodeHandle::operator==(std::nullptr_t) const
{
	return _index == -1;
}

bool NodeHandle::operator!=(std::nullptr_t) const
{
	return _index != -1;
}

NodeHandle& NodeHandle::operator=(NodeHandle other_)
{
	_index = other_._index;
	_graph = other_._graph;

	return *this;
}
