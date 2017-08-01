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
	
	const auto&			getWeight() const;
	const auto&			getPosition() const { return _position; }
	const auto*			getParent() const { return _parent; }
	void				setParent(const Node* node_);
	std::vector<Node*>	expand();

private:
	mutable std::map<Node*, float>
						_connections;
	sf::Vector2u 		_position;
	const Node*			_parent{nullptr};
	
public:
	enum class Tag
	{
		New,
		Open,
		Closed
	}				tag{Tag::New};
};

#endif // NODE_HPP