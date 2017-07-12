#ifndef GUI_INPUT_HANDLER_HPP
#define GUI_INPUT_HANDLER_HPP

#include <experimental/optional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Gui/Inputs.hpp>
#include <Gui/RawInputs.hpp>

namespace Gui
{

class InputHandler
{
public:
	const auto&				getInputs() { return _inputs; }
	void 					handleInput(const RawInputs& raw_inputs_);

private:
	Inputs 					_inputs;
	std::experimental::optional<sf::Event>
							_unhandled_queued_event;
};

} // namespace Gui

#endif // GUI_INPUT_HANDLER_HPP
