#include <Node.hpp>
#include <algorithm>
#include <Pathplanner.hpp>
#include <Graph.hpp>

Node::Node(sf::Vector2f position_)
	: _data_component{position_}
{
}

const NodeComponents::Data& Node::getData() const
{
	return _data_component; 
}

NodeComponents::Data& Node::getData(Key<Graph>)
{
	return _data_component;
}

const NodeComponents::Visualization& Node::getVisualization() const
{
	return _visualization_component;
}

NodeComponents::Visualization& Node::getVisualization(Key<Gui::AStarVisualizer>)
{
	return _visualization_component;
}

const NodeComponents::PathplanningData& Node::getPathplanningData() const
{
	return _pathplanning_data_component;
}

NodeComponents::PathplanningData& Node::getPathplanningData(PathplannerKey)
{
	return _pathplanning_data_component;
}


const NodeComponents::DStarData& Node::getDStarData() const
{
	return _dstar_data_component;
}

NodeComponents::DStarData& Node::getDStarData(Key<DStarPathplanner>)
{
	return _dstar_data_component;
}

float getWeight(Graph& graph_, const Node& from_, const Node& to_)
{
	const auto found{from_.getData().connections.find(graph_.getIndex(to_))};
	if (found != end(from_.getData().connections))
		return found->second;
	return std::numeric_limits<float>::infinity();
}

std::vector<Node*> computeSuccessors(const Graph& graph_, const Node* node_, Key<AStarPathplanner>)
{
	std::vector<Node*> successors;

	for (auto& [to_node_index, cost] : node_->getData().connections) {
		if (&graph_.getNode(to_node_index) != node_->getPathplanningData().parent)
			successors.push_back(const_cast<Node*>(&graph_.getNode(to_node_index)));
	}

	return successors;
}

std::vector<const Node*> computeSuccessors(const Graph& graph_, const Node* node_)
{
	std::vector<const Node*> successors;

	for (auto& [to_node_index, cost] : node_->getData().connections) {
		if (&graph_.getNode(to_node_index) != node_->getPathplanningData().parent)
			successors.push_back(&graph_.getNode(to_node_index));
	}

	return successors;
}
