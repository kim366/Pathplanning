#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <Gui/InputHandler.hpp>
#include <Gui/EntityManager.hpp>
#include <Gui/RawInputReceiver.hpp>
#include <Gui/Consts.hpp>

namespace Gui
{

class Core
{
public:
										Core();
	void 								loop();

private:
	std::unique_ptr<sf::RenderWindow>	_window{new sf::RenderWindow{{cst::Window::size, cst::Window::size}, cst::Window::title, sf::Style::Default, sf::ContextSettings{0, 0, 2}}};
	std::unique_ptr<RawInputReceiver>	_raw_input_receiver{new RawInputReceiver};
	std::unique_ptr<InputHandler>		_input_handler{new InputHandler};
	std::unique_ptr<EntityManager>		_entity_manager{new EntityManager};
};

} // namespace Gui


