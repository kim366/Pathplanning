#include <Gui/Inputs.hpp>

Gui::RawInputs::RawInputs()
{
	keyboard.fill(Button::RawState::Released);
	mouse.fill(Button::RawState::Released);
}

Gui::Inputs::Inputs()
{
	keyboard.fill(Button::State::Keyboard::NotPressed);
	mouse.fill(Button::State::Mouse::NoAction);
}