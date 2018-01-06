#include <Gui/Core.hpp>
#include <Graph.hpp>
#include <Grid.hpp>
#include <Gui/PathplannerVisualizer.hpp>

namespace Gui
{

Core::Core()
{
	auto grid{std::make_unique<Grid>(10, true)};
	// std::unique_ptr<PathplannerVisualizer> visualizer{new PathplannerVisualizer{std::make_unique<DStarPathplanner>(*grid), *grid, (*grid)[grid->toIndex({14, 15})], (*grid)[grid->toIndex({28, 1})]}};
	grid->disconnect({grid->toIndex({4, 3}), grid->toIndex({4, 2})});
	grid->disconnect({grid->toIndex({5, 3}), grid->toIndex({5, 2})});
	grid->disconnect({grid->toIndex({6, 3}), grid->toIndex({6, 2})});
	grid->disconnect({grid->toIndex({6, 3}), grid->toIndex({7, 3})});
	grid->disconnect({grid->toIndex({6, 4}), grid->toIndex({7, 4})});

	grid->disconnect({grid->toIndex({4, 3}), grid->toIndex({5, 2})});
	grid->disconnect({grid->toIndex({5, 3}), grid->toIndex({6, 2})});
	grid->disconnect({grid->toIndex({6, 3}), grid->toIndex({7, 2})});
	grid->disconnect({grid->toIndex({6, 4}), grid->toIndex({7, 3})});
	grid->disconnect({grid->toIndex({6, 5}), grid->toIndex({7, 4})});
	std::unique_ptr<PathplannerVisualizer> visualizer{new PathplannerVisualizer{std::make_unique<DStarPathplanner>(/*[] (...) { return 0; }, */*grid), *grid, (*grid)[grid->toIndex({4, 5})], (*grid)[grid->toIndex({8, 1})]}};
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
