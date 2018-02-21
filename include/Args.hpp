#pragma once

enum Mode
{
	PerfectGrid,
	GenerateMaze,
	RandomDist
};

struct Args
{
	Args(int argc, char const *argv[]);

	bool eight_connected;
	Mode mode;
	bool uninformed;
	int grid_size;
};