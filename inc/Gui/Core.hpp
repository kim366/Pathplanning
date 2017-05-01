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
	void 				run();

private:
	InputHandler		_input_handler{_window};
	EntityManager		_entity_manager{_input_handler.getInputs()};
	sf::RenderWindow	_window{{cst::Window::size, cst::Window::size}, cst::Window::title};
};

} // namespace Gui

#endif // GUI_CORE_HPP