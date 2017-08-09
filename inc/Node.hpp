#ifndef NODE_HPP
#define NODE_HPP

#include <unordered_map>
#include <vector>
#include <SFML/System/Vector2.hpp>

class Pathplanner;
class Graph;

class Node
{
	friend class Graph;

public:
						Node(sf::Vector2u position_);
	
	const float			getWeight(const Node* to_) const;
	const auto&			getPosition() const { return _position; }
	std::vector<Node*>	expand();

private:
	std::unordered_map<Node*, float>
						_connections;
	sf::Vector2u 		_position;

public:
	int					tag;
	const Node*			parent{nullptr};
	float				value{0.f};	
};

#endif // NODE_HPP