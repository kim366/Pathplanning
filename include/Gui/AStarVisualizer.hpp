#pragma once

#include <Gui/Entity.hpp>
#include <AStarPathplanner.hpp>
#include <Heuristics.hpp>

namespace Gui
{

class AStarVisualizer : public Entity
{
public:
							AStarVisualizer(Graph& graph_, Node* start_, Node* goal_);

private:
	virtual void 			update(float delta_time_, const Inputs& inputs_) override;

private:
	Graph&					_graph;
	AStarPathplanner		_find_shortest_path{_graph, Euclidean{}};
	PathplanningReturnType	_result;
	Node*					_start;
	Node*					_goal;
};

} // namespace Gui

