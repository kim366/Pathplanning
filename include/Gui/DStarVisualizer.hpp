#pragma once

#include <Gui/Entity.hpp>
#include <DStarPathplanner.hpp>
#include <Heuristics.hpp>

namespace Gui
{

class DStarVisualizer : public Entity
{
public:
							DStarVisualizer(Graph& graph_, NodeHandle start_, NodeHandle goal_);

private:
	virtual void 			update(float delta_time_, const Inputs& inputs_) override;

private:
	DStarPathplanner		_find_shortest_path;
	PathplanningReturnType	_result;
	NodeHandle				_start;
	NodeHandle				_goal;
};

} // namespace Gui
