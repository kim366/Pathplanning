#ifndef GUI_MOUSE_INPUT_TYPE_HPP
#define GUI_MOUSE_INPUT_TYPE_HPP

#include <experimental/optional>

namespace Gui
{

namespace MouseInputType
{

enum class Event
{
	Pressed,
	Clicked,
	Dropped
};

enum class State
{
	Released,
	Pressed,
	Dragged
};

struct Button
{
			Button() : state(State::Released) {}
	std::experimental::optional<Event>
			event;
	State 	state;
};

} // namespace InputType

} // namespace Gui

#endif // MOUSE_STATE_HPP