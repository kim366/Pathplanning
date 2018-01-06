#pragma once

#include <cstddef>
#include <functional>

class Graph;
class Node;

class NodePtr
{
friend Graph; 
friend class std::hash<NodePtr>;

public:
				NodePtr(std::nullptr_t);
				NodePtr(int index_, Graph& graph_);
				
	Node* 		operator->();
	const Node* operator->() const;
	Node& 		operator*();
	const Node& operator*() const;

	bool 		operator==(NodePtr other_) const;
	bool		operator!=(NodePtr other_) const;

	bool		operator==(std::nullptr_t) const;
	bool 		operator!=(std::nullptr_t) const;
	NodePtr& 	operator=(NodePtr other_);

	int			getIndex() const;
	Graph&		getGraph();

private:
	int 		_index;
	Graph* 		_graph;
};

namespace std
{
	template<>
	struct hash<NodePtr>
	{
		size_t operator()(NodePtr node_) const
		{
			return hash<int>()(node_._index);
		}
	};
}
