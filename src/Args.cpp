#include <Args.hpp>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std::literals::string_literals;

Args::Args(int argc, char const *argv[])
	: grid_size{10}
{
	std::vector<std::string> args(argv + 1, argv + argc);

	auto contains{[&] (std::string s_) -> bool
	{
		if (!args.empty() && args[0][0] == '-' && args[0].find(s_) != std::string::npos)
			return true;
		return std::find(args.begin(), args.end(), "-" + s_) != args.end();
	}};

	auto contains_and_next_is_valid{[&] (std::string s_) -> std::pair<bool, std::string>
	{
		auto found{std::find(args.begin(), args.end(), "-" + s_)};
		if (found != args.end() && found != args.end() - 1)
			return {true, *++found};
		return {false, ""};
	}};

	if (contains("-h"))
	{
		std::cout <<
R"(Usage: gui [options]
Options:
  -h                        Display this information.
  -e                        Make the generated grid eight-connected.
  -u                        Make the path planners have limited environmental knowledge
  -s <size>                 Set the grid size (default: 10).
  -m {perfect|maze|random}  Set grid generation mode (default: perfect).
  -a                        Animate procedure (future version).
  -i {a*|d*|dijkstra}       Initial search algorithm
)";
		std::exit(EXIT_SUCCESS);
	}

	eight_connected = contains("e");
	uninformed = contains("u");

	if (auto [contains, next]{contains_and_next_is_valid("s")}; contains)
		grid_size = std::stoi(next);

	if (auto [contains, next]{contains_and_next_is_valid("m")}; contains)
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

	uninformed = true;
	
}
