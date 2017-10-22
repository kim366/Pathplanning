#pragma once

#include <Gui/Entity.hpp>
#include <AStarPathplanner.hpp>
#include <Heuristics.hpp>

namespace Gui
{

class AStarVisualizer : public Entity
{
public:
	AStarVisualizer(Graph& graph_, const Node* start_, const Node* goal_);

private:
	virtual void 	update(float delta_time_, const Inputs& inputs_) override;

private:
	Graph&						_graph;
	AStarPathplanner<Octile>	_find_shortest_path{_graph};
	std::vector<const Node*>	_found_path;
	std::set<const Node*>		_examined_nodes;
	const Node*					_start;
	const Node*					_goal;
};

} // namespace Gui

