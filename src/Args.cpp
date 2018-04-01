#include <Args.hpp>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std::literals::string_literals;

Args::Args(int argc, char const *argv[])
	: grid_size{10}
	, initial_pathplanner{NoPathplanner}
	, start_position{Corner}
	, frame_limit{10}
{
	std::vector<std::string> args(argv + 1, argv + argc);

	auto contains{[&] (std::string s_) -> bool
	{
		if (!args.empty() && args[0][0] == '-' && args[0][1] != '-' && args[0].find(s_) != std::string::npos)
			return true;
		return std::find(args.begin(), args.end(), "-" + s_) != args.end();
	}};

	auto contains_and_next_is_valid{[&] (std::string s_, std::string s2_) -> std::pair<bool, std::string>
	{
		for (auto s : {s_, s2_})
		{
			auto found{std::find(args.begin(), args.end(), "-" + s)};
			if (found != args.end() && found != args.end() - 1)
				return {true, *++found};
		}
		return {false, ""};
	}};

	if (contains("h") || contains("-help"))
	{
		std::cout <<
R"(Usage: gui [options]
Options:
  -h, --help             Display this information.
  -e, --eight-connected  Make the generated grid eight-connected.
  -u                     Make the path planners have limited environmental knowledge
  -s, --size <size>      Set the grid size (default: 10).
  -l, --limit <limit>    Set the framerate limit (default: 10).
  -m, --mode {perfect|maze|random}
                         Set grid generation mode (default: perfect).
  -a, --animate          Animate procedure.
  -d                     Disconnect crossing edges.
  -f, --seed <seed>      Seed th
  e random number generators.
  -i, --initial-search {astar|dstar|dijkstra}
                         Choose Initial search algorithm.
  -n, --start {center|corner}
                         Set node start position (default: corner).
)";
		std::exit(EXIT_SUCCESS);
	}

	eight_connected = contains("e") || contains("-eight-connected");
	animate = contains("a") || contains("-animate");
	uninformed = contains("u");
	disconnect_crossing_edges = contains("d");

	if (auto [contains, next]{contains_and_next_is_valid("n", "n")}; contains)
	{
		if (next == "corner")
			start_position = Corner;
		else if (next == "center")
			start_position = Center;
	}

	if (auto [contains, next]{contains_and_next_is_valid("s", "-size")}; contains)
		grid_size = std::stoi(next);

	if (auto [contains, next]{contains_and_next_is_valid("l", "-limit")}; contains)
		frame_limit = std::stoi(next);

	if (auto [contains, next]{contains_and_next_is_valid("m", "-mode")}; contains)
	{		
		if (next == "perfect")
			mode = PerfectGrid;
		else if (next == "maze")
		{
			mode = GenerateMaze;
			uninformed = false;
		}
		else if (next == "random")
			mode = RandomDist;
	}

	if (auto [contains, next]{contains_and_next_is_valid("i", "-initial-search")}; contains)
	{		
		if (next == "dstar")
			initial_pathplanner = DStar;
		else if (next == "astar")
			initial_pathplanner = AStar;
		else if (next == "dijkstra")
			initial_pathplanner = Dijkstra;
		else
			initial_pathplanner = NoPathplanner;
	}

	if (auto [contains, next]{contains_and_next_is_valid("f", "-seed")}; contains)	
		seed = std::stoi(next);
}
