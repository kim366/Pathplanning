#pragma once

#include <unordered_map>
#include <vector>
#include <SFML/System/Vector2.hpp>

class Node;

namespace NodeComponents
{

struct Data
{
										Data(sf::Vector2f position_) : position{position_} {}

	const sf::Vector2f					position;
	std::unordered_map<Node*, float>	connections;
};

struct PathplanningData
{
	int		tag;
	Node*	parent{nullptr};
	float	value{0.f};	
	float	heuristic_value{0.f};
	float	to_start_value{0.f};
};

struct Visualization
{
	enum Status
	{
		Standard,
		OnPath,
		Examined
	} status;
};

} // namespace NodeComponents