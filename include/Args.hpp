#pragma once

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
	bool uninformed;
	int grid_size;
};
