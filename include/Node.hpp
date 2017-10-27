#pragma once

#include <Key.hpp>
#include <SFML/System/Vector2.hpp>
#include <NodeComponents.hpp>

class Graph;
class AStarPathplanner;

namespace Gui { class AStarVisualizer; }

class Node
{
public:
											Node(sf::Vector2f position_);

	const NodeComponents::Data& 			getData() const;
	NodeComponents::Data& 					getData(Key<Graph>);

	const NodeComponents::Visualization&	getVisualization() const;
	NodeComponents::Visualization&			getVisualization(Key<Gui::AStarVisualizer>);

	const NodeComponents::Pathplanning& 	getPathplanningData() const;
	NodeComponents::Pathplanning& 			getPathplanningData(Key<AStarPathplanner>);

	const float								getWeight(const Node* to_) const;
	std::vector<Node*>						expand() const;

private:
	NodeComponents::Data					_data_component;
	NodeComponents::Visualization			_visualization_component;
	NodeComponents::Pathplanning			_pathplanning_component;
};

