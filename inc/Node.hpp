#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include <SFML/System/Vector2.hpp>

class Graph;

class Node
{
	friend class Graph;

public:
					Node(sf::Vector2u position_) : _position(position_) {}

	const auto&		getWeight(const Node* node_) const { return _connections[const_cast<Node*>(node_)]; }
	const auto&		getPosition() const { return _position; }

private:
	mutable std::map<Node*, float> 
					_connections;
	sf::Vector2u 	_position;	
};

#endif // NODE_HPP