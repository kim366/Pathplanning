#include <Gui/Core.hpp>

namespace Gui
{

Core::Core()
	: _entity_manager(_input_handler.getInputs())
{
}

void Core::run()
{
	sf::Clock clock;
	while (true)
	{
		sf::Time delta_time = clock.restart();
		if(_input_handler.handleInput())
			return;
		_entity_manager.updateEntities(delta_time.asSeconds());
		_entity_manager.drawEntities();
	}
}

} // namespace Gui
