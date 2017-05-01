#include <Gui/Core.hpp>

namespace Gui
{

void Core::loop()
{
	sf::Clock clock;
	while (true)
	{
		sf::Time delta_time = clock.restart();
		
		if(_input_handler.handleInput())
			return;

		_entity_manager.updateEntities(delta_time.asSeconds());
		_entity_manager.drawEntities(_window);
	}
}

} // namespace Gui
