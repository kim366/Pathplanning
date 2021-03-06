#pragma once

#include <Key.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <vector>
#include <PathplanningTag.hpp> 
#include <NodePtr.hpp>

struct Node
{
					Node(sf::Vector2f position_);

	// Common Data
	sf::Vector2f	position;
	std::unordered_map<NodePtr, float>
					neighbors;

	// Used by Dijkstra's Algorithm, A* and D*
	PathplanningTag	tag;
	NodePtr			parent;

	// Used by A*
	float			to_start_value;
	float			heuristic_value;

	// Used by D*
	float 			key_value;

	// Used by uninformed Dijkstra's Algorithm and A*
	NodePtr			child;

	enum VisualizationStatus
	{
		Standard,
		OnPath,
		Examined
	} visualization_status;
	NodePtr visualization_parent;

	// Used by Maze Generator
};

float 					getWeight(NodePtr from_, NodePtr to_);
std::vector<NodePtr> 	computeSuccessors(NodePtr node_);
