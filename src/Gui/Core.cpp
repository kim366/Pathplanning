#include <Gui/Core.hpp>
#include <Graph.hpp>
#include <Grid.hpp>
#include <Gui/PathplannerVisualizer.hpp>
#include <cmath>
#include <random>
#include <algorithm>

namespace Gui
{

Core::Core()
{
	const int grid_size{80};
	auto grid{std::make_unique<Grid>(grid_size, false)};

#ifdef UNINFORMED
	std::unique_ptr<PathplannerVisualizer> visualizer{new PathplannerVisualizer{std::make_unique<DStarPathplanner>(*grid), *grid, (*grid)[grid->toIndex({0, grid_size - 1})], (*grid)[grid->toIndex({grid_size - 1, 0})]}};
#endif

	// std::mt19937 rng{std::random_device{}()};
	// rng.seed(80);
	// std::normal_distribution random_node{25., 10.};

	// for (int counter{0}; counter < 5000; ++counter)
	// {
	// 	int chosen_node_index(grid->toIndex({std::clamp<int>(random_node(rng), 0, grid_size - 1), std::clamp<int>(random_node(rng), 0, grid_size - 1)}));

	// 	for (int second_counter{0}; second_counter < 2; ++second_counter)
	// 	{
	// 		if ((*grid)[chosen_node_index]->neighbors.size() <= 5)
	// 			break;

	// 		std::uniform_int_distribution random_neighbor(0, (*grid)[chosen_node_index]->neighbors.size() - 1);
	// 		auto neighbor_it{(*grid)[chosen_node_index]->neighbors.begin()};
	// 		std::advance(neighbor_it, random_neighbor(rng));
	// 		grid->disconnect({chosen_node_index, neighbor_it->first.getIndex()});
	// 	}
	// }

#ifndef UNINFORMED
	std::unique_ptr<PathplannerVisualizer> visualizer{new PathplannerVisualizer{std::make_unique<DStarPathplanner>(*grid), *grid, (*grid)[grid->toIndex({0, grid_size - 1})], (*grid)[grid->toIndex({grid_size - 1, 0})]}};
#endif

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
