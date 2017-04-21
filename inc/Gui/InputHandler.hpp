#ifndef GUI_INPUT_HANDLER_HPP
#define GUI_INPUT_HANDLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <Gui/Inputs.hpp>

namespace Gui
{

class InputHandler
{
public:
	explicit 			InputHandler(sf::RenderWindow& window_);
	const auto&			getInputs() { return _inputs; }
	bool 				handleInput();

private:
	RawInputs			_raw_inputs;
	Inputs 				_inputs;
	sf::RenderWindow&	_window;
};

} // namespace Gui

#endif // GUI_INPUT_HANDLER_HPP