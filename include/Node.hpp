#pragma once

#include <Key.hpp>
#include <SFML/System/Vector2.hpp>
#include <NodeComponents.hpp>

class Graph;
class AStarPathplanner;
class DStarPathplanner;

namespace Gui { class AStarVisualizer; }

class Node
{
public:
											Node(sf::Vector2f position_);

	const NodeComponents::Data&				getData() const;
	NodeComponents::Data&					getData(Key<Graph>);

	const NodeComponents::Visualization&	getVisualization() const;
	NodeComponents::Visualization&			getVisualization(VisualizationKey);

	const NodeComponents::PathplanningData&	getPathplanningData() const;
	NodeComponents::PathplanningData&		getPathplanningData(PathplannerKey);

	const NodeComponents::DStarData&		getDStarData() const;
	NodeComponents::DStarData&				getDStarData(Key<DStarPathplanner>);

private:
	NodeComponents::Data					_data_component;
	NodeComponents::Visualization 			_visualization_component;
	NodeComponents::PathplanningData 		_pathplanning_data_component;
	NodeComponents::DStarData				_dstar_data_component;
};

float getWeight(Graph& graph_, const Node& from_, const Node& to_);
std::vector<Node*> computeSuccessors(const Graph& graph_, const Node* node_, Key<AStarPathplanner>);
std::vector<const Node*> computeSuccessors(const Graph& graph_, const Node* node_);
