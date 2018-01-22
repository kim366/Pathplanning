#include <NodePtr.hpp>
#include <Graph.hpp>
#include <cassert>

NodePtr::NodePtr(std::nullptr_t)
	: _index{-1}
	, _graph{nullptr}
{
}

NodePtr::NodePtr(int index_, Graph& graph_)
	: _index{index_}
	, _graph{&graph_}
{
}

Node* NodePtr::operator->()
{
	return &**this;
}

const Node* NodePtr::operator->() const
{
	return &**this;
}

Node& NodePtr::operator*()
{
	assert(_index > -1);
	return _graph->_nodes[_index];
}

const Node& NodePtr::operator*() const
{
	assert(_index > -1);
	return _graph->_nodes[_index];
}

// bool NodePtr::operator<(NodePtr other_) const
// {
// 	return _index < other_._index;
// }

bool NodePtr::operator==(NodePtr other_) const
{
	return _index == other_._index && _graph == other_._graph;
}

bool NodePtr::operator!=(NodePtr other_) const
{
	return !(*this == other_);
}

bool NodePtr::operator==(std::nullptr_t) const
{
	return _index == -1;
}

bool NodePtr::operator!=(std::nullptr_t) const
{
	return _index != -1;
}

int NodePtr::getIndex() const
{
	assert(_index > -1);
	return _index;
}

Graph& NodePtr::getGraph()
{
	return *_graph;
}
