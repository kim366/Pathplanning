#pragma once

#include <Gui/Entity.hpp>
#include <AStarPathplanner.hpp>
#include <Heuristics.hpp>

namespace Gui
{

class AStarVisualizer : public Entity
{
public:
							AStarVisualizer(Graph& graph_, NodeHandle start_, NodeHandle goal_);

private:
	virtual void 			update(float delta_time_, const Inputs& inputs_) override;

private:
	Graph& 					_graph; 
	AStarPathplanner		_find_shortest_path{Manhattan{}};
	PathplanningReturnType	_result;
	NodeHandle				_start;
	NodeHandle				_goal;
};

} // namespace Gui

