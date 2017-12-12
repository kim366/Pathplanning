#include <Gui/Core.hpp>
#include <Graph.hpp>
#include <Grid.hpp>
#include <Gui/AStarVisualizer.hpp>

namespace Gui
{

Core::Core()
{
	auto grid{std::make_unique<Grid>(30, true)};
	auto astar_visualizer{std::make_unique<AStarVisualizer>(*grid, grid->toIndex({14, 15}), grid->toIndex({28, 1}))};
	_entity_manager->addEntity(std::move(grid));
	_entity_manager->addEntity(std::move(astar_visualizer));
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
