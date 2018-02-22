#pragma once

#include <optional>

enum Mode
{
	PerfectGrid,
	GenerateMaze,
	RandomDist
};

enum InitialPathplanner
{
	AStar,
	DStar,
	Dijkstra,
	NoPathplanner
};

struct Args
{
	Args(int argc, char const *argv[]);

	bool eight_connected;
	Mode mode;
	InitialPathplanner initial_pathplanner;
	bool disconnect_crossing_edges;
	std::optional<int> seed;
	bool uninformed;
	int grid_size;
};
