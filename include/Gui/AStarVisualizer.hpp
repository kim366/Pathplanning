#pragma once

#include <Gui/Entity.hpp>
#include <AStarPathplanner.hpp>
#include <Heuristics.hpp>

namespace Gui
{

class AStarVisualizer : public Entity
{
public:
							AStarVisualizer(Graph& graph_, int start_, int goal_);

private:
	virtual void 			update(float delta_time_, const Inputs& inputs_) override;

private:
	Graph&					_graph;
	AStarPathplanner		_find_shortest_path{_graph, Manhattan{}};
	PathplanningReturnType	_result;
	int						_start;
	int						_goal;
};

} // namespace Gui

