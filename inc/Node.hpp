#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include <SFML/System/Vector2.hpp>

class Edge;

struct Node
{
							Node(sf::Vector2u position_) : _position(position_) {}

	std::map<Node*, Edge*> 	_edges;
	sf::Vector2u 			_position;	
};

#endif // NODE_HPP