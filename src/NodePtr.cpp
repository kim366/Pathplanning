#include <NodePtr.hpp>
#include <Graph.hpp>

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
	return &_graph->_nodes[_index];
}

const Node* NodePtr::operator->() const
{
	return &_graph->_nodes[_index];
}

Node& NodePtr::operator*()
{
	return _graph->_nodes[_index];
}

const Node& NodePtr::operator*() const
{
	return _graph->_nodes[_index];
}

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

NodePtr& NodePtr::operator=(NodePtr other_)
{
	_index = other_._index;
	_graph = other_._graph;

	return *this;
}

int NodePtr::getIndex() const
{
	return _index;
}
