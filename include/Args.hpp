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

enum StartPosition
{
	Center,
	Corner
};

struct Args
{
	Args(int argc, char const *argv[]);

	bool eight_connected;
	Mode mode;
	InitialPathplanner initial_pathplanner;
	bool disconnect_crossing_edges;
	bool animate;
	std::optional<int> seed;
	bool uninformed;
	int grid_size;
	int frame_limit;
	StartPosition start_position;
};
