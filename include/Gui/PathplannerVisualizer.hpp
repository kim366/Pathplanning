#pragma once

#include <Gui/Entity.hpp>
#include <DStarPathplanner.hpp>
#include <AStarPathplanner.hpp>
#include <Heuristics.hpp>

namespace Gui
{

class PathplannerVisualizer : public Entity
{
public:
									PathplannerVisualizer(std::unique_ptr<Pathplanner>&& pathplanner_, Graph& graph_, NodeHandle start_, NodeHandle goal_);

private:
	virtual void 					update(float delta_time_, const Inputs& inputs_) override;

private:
	std::unique_ptr<Pathplanner>	_pathplanner;
	Graph&							_graph;
	NodeHandle						_start;
	NodeHandle						_goal;
	
};

} // namespace Gui
