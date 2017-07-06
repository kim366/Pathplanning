#ifndef GUI_MOUSE_INPUT_TYPE_HPP
#define GUI_MOUSE_INPUT_TYPE_HPP

#include <experimental/optional>

namespace Gui
{

namespace MouseInputType
{

enum class Event
{
	None,
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
	Event	event{Event::None};
	State 	state{State::Released};
};

} // namespace InputType

} // namespace Gui

#endif // MOUSE_STATE_HPP