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

	const NodeComponents::Data&				getData() const;
	NodeComponents::Data&					getData(Key<Graph>);

	const NodeComponents::Visualization&	getVisualization() const;
	NodeComponents::Visualization&			getVisualization(Key<Gui::AStarVisualizer>);

	const NodeComponents::PathplanningData&	getPathplanningData() const;
	NodeComponents::PathplanningData&		getPathplanningData(Key<AStarPathplanner>);


private:
	NodeComponents::Data					_data_component;
	NodeComponents::Visualization 			_visualization_component;
	NodeComponents::PathplanningData 		_pathplanning_data_component;
};

float getWeight(const Node* from_, const Node* to_);
std::vector<Node*> computeSuccessors(const Node* node_, Key<AStarPathplanner>);
std::vector<const Node*> computeSuccessors(const Node* node_);
