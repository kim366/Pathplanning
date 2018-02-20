#include <Gui/Core.hpp>
#include <Graph.hpp>
#include <Grid.hpp>
#include <Gui/PathplannerVisualizer.hpp>
#include <cmath>
#include <random>
#include <algorithm>

namespace Gui
{

Core::Core(Args args_)
{
	const int grid_size{args_.grid_size};
	auto grid{std::make_unique<Grid>(grid_size, args_.eight_connected)};
	Grid perfect_grid{*grid};

	if (args_.mode == RandomDist)
	{
		std::mt19937 rng{std::random_device{}()};
		rng.seed(80);
		std::normal_distribution random_node{25., 10.};

		for (int counter{0}; counter < 5000; ++counter)
		{
			int chosen_node_index(grid->toIndex({std::clamp<int>(random_node(rng), 0, grid_size - 1), std::clamp<int>(random_node(rng), 0, grid_size - 1)}));

			for (int second_counter{0}; second_counter < 2; ++second_counter)
			{
				if ((*grid)[chosen_node_index]->neighbors.size() <= 5)
					break;

				std::uniform_int_distribution<int> random_neighbor(0, (*grid)[chosen_node_index]->neighbors.size() - 1);
				auto neighbor_it{(*grid)[chosen_node_index]->neighbors.begin()};
				std::advance(neighbor_it, random_neighbor(rng));
				grid->disconnect({chosen_node_index, neighbor_it->first.getIndex()});
			}
		}
	}

	std::unique_ptr<PathplannerVisualizer> visualizer{!args_.uninformed ? new PathplannerVisualizer{std::make_unique<DStarPathplanner>(*grid), *grid, (*grid)[grid->toIndex({1, grid_size - 2})], (*grid)[grid->toIndex({grid_size - 2, 1})]} : new PathplannerVisualizer{std::make_unique<DStarPathplanner>(perfect_grid), *grid, (*grid)[grid->toIndex({1, grid_size - 2})], (*grid)[grid->toIndex({grid_size - 2, 1})]}};

	if (args_.mode == GenerateMaze)
		grid->generateMaze();

	_entity_manager->addEntity(std::move(grid));
	_entity_manager->addEntity(std::move(visualizer));
	_window->setFramerateLimit(10);
}

void Core::loop()
{
	sf::Clock clock;
	while (true)
	{
		sf::Time delta_time = clock.restart();
		
		_raw_input_receiver->receiveInput(_window);

		if (_raw_input_receiver->shouldWindowClose())
			return;

		_input_handler->handleInput(_raw_input_receiver->getInputs());

		_entity_manager->updateEntities(delta_time.asSeconds(), _input_handler->getInputs());
		_entity_manager->drawEntities(_window);
	}
}

} // namespace Gui
