#ifndef GUI_CORE_HPP
#define GUI_CORE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <Gui/InputHandler.hpp>
#include <Gui/EntityManager.hpp>
#include <Gui/Consts.hpp>

namespace Gui
{

class Core
{
public:
	void 								loop();

private:
	std::unique_ptr<sf::RenderWindow>	_window{new sf::RenderWindow{{cst::Window::size, cst::Window::size}, cst::Window::title}};
	std::unique_ptr<InputHandler>		_input_handler{new InputHandler{*_window}};
	std::unique_ptr<EntityManager>		_entity_manager{new EntityManager{_input_handler->getInputs()}};
};

} // namespace Gui

#endif // GUI_CORE_HPP