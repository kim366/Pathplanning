#include <Node.hpp>
#include <algorithm>
#include <Pathplanner.hpp>

Node::Node(sf::Vector2f position_)
	: _data_component{position_}
{
}

float Node::getWeight(const Node* to_) const
{
	auto found{_data_component.connections.find(const_cast<Node*>(to_))};
	if (found != end(_data_component.connections))
		return found->second;
	return std::numeric_limits<float>::infinity();
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

const NodeComponents::Pathplanning& Node::getPathplanningData() const
{
	return _pathplanning_component;
}

NodeComponents::Pathplanning& Node::getPathplanningData(Key<AStarPathplanner>)
{
	return _pathplanning_component;
}


std::vector<Node*> computeSuccessors(const Node* node_, Key<AStarPathplanner>)
{
	std::vector<Node*> successors;

	for (auto& [to_node, cost] : node_->getData().connections) {
		if (to_node != node_->getPathplanningData().parent)
			successors.push_back(to_node);
	}

	return successors;
}

std::vector<const Node*> computeSuccessors(const Node* node_)
{
	std::vector<const Node*> successors;

	for (auto& [to_node, cost] : node_->getData().connections) {
		if (to_node != node_->getPathplanningData().parent)
			successors.push_back(to_node);
	}

	return successors;
}
