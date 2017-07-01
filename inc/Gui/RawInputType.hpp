#ifndef GUI_RAW_INPUT_TYPE_HPP
#define GUI_RAW_INPUT_TYPE_HPP

namespace Gui
{

namespace RawInputType
{

enum class Event
{
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
			Button() : state(State::Released) {}
	Event 	event;
	State 	state;
};

} // namespace RawInputType

} // namespace Gui

#endif // GUI_RAW_INPUT_TYPE_HPP