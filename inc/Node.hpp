#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include <vector>
#include <SFML/System/Vector2.hpp>

class Graph;

class Node
{
	friend class Graph;

public:
						Node(sf::Vector2u position_) : _position(position_) {}
	
	const float			getWeight() const;
	const auto&			getPosition() const { return _position; }
	std::vector<Node*>	expand();

private:
	mutable std::map<Node*, float>
						_connections;
	sf::Vector2u 		_position;

public:
	enum class Tag
	{
		New,
		Open,
		Closed
	}					tag{Tag::New};
	const Node*			parent{nullptr};
	float				value{0};	
};

#endif // NODE_HPP