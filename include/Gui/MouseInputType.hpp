#pragma once

#include <optional>

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
	std::optional<sf::Vector2u>
			pressed_down_cursor_position; // Position at which *this* button was pressed
	State 	last_frame_state{State::Released};
};

} // namespace InputType

} // namespace Gui


