#ifndef NODE_HPP
#define NODE_HPP

#include <map>

class Edge;
class Graph;

class Node
{
	friend class Graph;

private:
	std::map<Node*, Edge*> _edges;

private:
		
};

#endif // NODE_HPP