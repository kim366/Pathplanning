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
									PathplannerVisualizer(std::unique_ptr<Pathplanner>&& pathplanner_, Graph& graph_, NodePtr start_, NodePtr goal_, bool uninformed_);

private:
	virtual void 					update(float delta_time_, const Inputs& inputs_) override;

private:
	std::unique_ptr<Pathplanner>	_pathplanner;
	Graph&							_graph;
	Graph							_map;
	NodePtr							_start;
	NodePtr							_goal;
	bool							_uninformed;
};

} // namespace Gui
