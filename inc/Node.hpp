#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include <SFML/System/Vector2.hpp>

class Edge;
class Graph;

class Node
{
	friend class Graph;

public:
							Node(sf::Vector2u position_) : _position(position_) {}

	const auto&				getEdges() const { return _edges; }
	const auto&				getPosition() const { return _position; }

	std::map<Node*, Edge*> 	_edges;
	sf::Vector2u 			_position;	
};

#endif // NODE_HPP