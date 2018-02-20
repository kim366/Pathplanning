#include <Args.hpp>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

Args::Args(int argc, char const *argv[])
	: grid_size{10}
{
	std::vector<std::string> args(argv + 1, argv + argc);

	auto contains{[&] (std::string s_)
	{
		return std::find(args.begin(), args.end(), s_) != args.end();
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
)";
		std::exit(EXIT_SUCCESS);
	}

	eight_connected = contains("-e");
	uninformed = contains("-u");

	if (auto found{std::find(args.begin(), args.end(), "-s")}; found != args.end() && found != args.end() - 1)
		grid_size = std::stoi(*++found);

	if (auto found{std::find(args.begin(), args.end(), "-m")}; found != args.end() && found != args.end() - 1)
	{
		auto next{*++found};
		
		if (next == "perfect")
			mode = PerfectGrid;
		else if (next == "maze")
			mode = GenerateMaze;
		else if (next == "random")
			mode = RandomDist;
	}
}
