#pragma once

template <typename T>
class Key
{
	friend T;
	Key() {}; // must not be `= default`
	Key(Key const&) {};
};

class PathplannerKey
{
	friend class AStarPathplanner;
	friend class DStarPathplanner;
	
	PathplannerKey() {}; // must not be `= default`
	PathplannerKey(PathplannerKey const&) {};	
};

namespace Gui
{
	class AStarVisualizer;
	class DStarVisualizer;
}

class VisualizationKey
{
	friend Gui::AStarVisualizer;
	friend Gui::DStarVisualizer;
	
	VisualizationKey() {}; // must not be `= default`
	VisualizationKey(VisualizationKey const&) {};	
};
