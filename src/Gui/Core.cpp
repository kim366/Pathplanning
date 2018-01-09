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
	const int grid_size{50};
	auto grid{std::make_unique<Grid>(grid_size, true)};
	// std::unique_ptr<PathplannerVisualizer> visualizer{new PathplannerVisualizer{std::make_unique<DStarPathplanner>(*grid), *grid, (*grid)[grid->toIndex({14, 15})], (*grid)[grid->toIndex({28, 1})]}};
	// grid->disconnect({grid->toIndex({4, 3}), grid->toIndex({4, 2})});
	// grid->disconnect({grid->toIndex({5, 3}), grid->toIndex({5, 2})});
	// grid->disconnect({grid->toIndex({6, 3}), grid->toIndex({6, 2})});
	// grid->disconnect({grid->toIndex({6, 3}), grid->toIndex({7, 3})});
	// grid->disconnect({grid->toIndex({6, 4}), grid->toIndex({7, 4})});

	// grid->disconnect({grid->toIndex({4, 3}), grid->toIndex({5, 2})});
	// grid->disconnect({grid->toIndex({5, 3}), grid->toIndex({6, 2})});
	// grid->disconnect({grid->toIndex({6, 3}), grid->toIndex({7, 2})});
	// grid->disconnect({grid->toIndex({6, 4}), grid->toIndex({7, 3})});
	// grid->disconnect({grid->toIndex({6, 5}), grid->toIndex({7, 4})});
	std::unique_ptr<PathplannerVisualizer> visualizer{new PathplannerVisualizer{std::make_unique<DStarPathplanner>(/*[] (...) { return 0; }, */*grid), *grid, (*grid)[grid->toIndex({16, 33})], (*grid)[grid->toIndex({33, 16})]}};

	std::mt19937 rng{std::random_device{}()};
	// std::uniform_int_distribution<int> random_node(0, std::pow(grid_size, 2) - 1);
	std::normal_distribution random_node{25., 10.};

	for (int counter{0}; counter < 5000; ++counter)
	{
		int chosen_node_index(grid->toIndex({std::clamp<int>(random_node(rng), 0, 49), std::clamp<int>(random_node(rng), 0, 49)}));

		for (int second_counter{0}; second_counter < 3; ++second_counter)
		{
			if ((*grid)[chosen_node_index]->neighbors.size() <= 3)
				break;

			std::uniform_int_distribution<int> random_neighbor(0, (*grid)[chosen_node_index]->neighbors.size() - 1);
			auto neighbor_it{(*grid)[chosen_node_index]->neighbors.begin()};
			std::advance(neighbor_it, random_neighbor(rng));
			grid->disconnect({chosen_node_index, neighbor_it->first.getIndex()});
		}
	}

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
