#pragma once

#include <cstddef>
#include <functional>

class Graph;
class Node;

class NodeHandle
{
friend Graph; 
friend class std::hash<NodeHandle>;

public:
				NodeHandle();
				NodeHandle(int index_, Graph& graph_);
				
	Node* 		operator->();
	const Node* operator->() const;
	Node& 		operator*();
	const Node& operator*() const;

	bool 		operator==(NodeHandle other_) const;
	bool		operator!=(NodeHandle other_) const;
	// bool 		operator==(Node* other_) const;
	// bool		operator!=(Node* other_) const;

				operator bool() const;
	NodeHandle& operator=(NodeHandle other_);

private:
	int 		_index;
	Graph* 		_graph;
};

namespace std
{
	template<>
	struct hash<NodeHandle>
	{
		size_t operator()(NodeHandle node_) const
		{
			return hash<int>()(node_._index);
		}
	};
}
