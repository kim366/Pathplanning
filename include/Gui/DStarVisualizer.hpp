#pragma once

#include <Gui/Entity.hpp>
#include <DStarPathplanner.hpp>

namespace Gui
{

class DStarVisualizer : public Entity
{
public:
							DStarVisualizer(Graph& graph_, int start_, int goal_);

private:
	virtual void 			update(float delta_time_, const Inputs& inputs_) override;

private:
	Graph&					_graph;
	DStarPathplanner		_find_shortest_path{_graph};
	PathplanningReturnType	_result;
	int						_start;
	int						_goal;
};

} // namespace Gui

