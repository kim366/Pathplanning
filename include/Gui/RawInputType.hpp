#pragma once

#include <optional>
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
};

} // namespace RawInputType

} // namespace Gui


