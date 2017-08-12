#include <Gui/Core.hpp>
#include <Graph.hpp>
#include <Grid.hpp>

namespace Gui
{

Core::Core()
{
	auto grid{std::make_unique<Grid>(5, true)};
	grid->disconnect({2, 3});
	grid->disconnect({grid->toIndex({2,0}), grid->toIndex({3,1})});
	_entity_manager->addEntity(std::move(grid));
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
