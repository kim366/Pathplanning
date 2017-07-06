#ifndef GUI_RAW_INPUT_TYPE_HPP
#define GUI_RAW_INPUT_TYPE_HPP

#include <experimental/optional>
#include <SFML/Window/Event.hpp>

namespace Gui
{

namespace RawInputType
{

enum class Event
{
	None,
	Released,
	Pressed	
};

enum class State
{
	Released,
	Pressed
};

struct Button
{
	Event	event{Event::None};
	State 	state{State::Released};

	std::experimental::optional<sf::Event> queued_tactile_event; // Not nothing if two tactile Events in the same frame
};

} // namespace RawInputType

} // namespace Gui

#endif // GUI_RAW_INPUT_TYPE_HPP