#pragma once

#include <unordered_map>
#include <vector>
#include <SFML/System/Vector2.hpp>

class Pathplanner;
class Graph;

class Node
{
	friend class Graph;

public:
						Node(sf::Vector2f position_);
	
	const float			getWeight(const Node* to_) const;
	const auto&			getPosition() const { return _position; }
	std::vector<Node*>	expand() const;

private:
	std::unordered_map<Node*, float>
						_connections;
	sf::Vector2f 		_position;

public:
	int					tag;
	const Node*			parent{nullptr};
	float				value{0.f};	
	float				heuristic_value{0.f};
	float				to_start_value{0.f};
	enum Status
	{
		Standard,
		OnPath,
		Examined
	}					status;
};

