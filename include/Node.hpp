#pragma once

#include <Key.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <vector>
#include <PathplanningTag.hpp> 
#include <NodeHandle.hpp>

struct Node
{
					Node(sf::Vector2f position_);

	// Common Data
	sf::Vector2f	position;
	std::unordered_map<NodeHandle, float>
					neighbors;

	// Used by Dijkstra's Algorithm, A* and D*
	PathplanningTag	tag;
	NodeHandle		parent;
	float			value;	
	float			to_start_value;

	// Used by A* and D*
	float			heuristic_value;

	// Used by D*
	float 			previous_heuristic_value;
	float 			key_value;

	enum VisualizationStatus
	{
		Standard,
		OnPath,
		Examined
	} visualization_status;
};

float 					getWeight(const NodeHandle from_, const NodeHandle to_);
std::vector<NodeHandle> computeSuccessors(const NodeHandle node_);
