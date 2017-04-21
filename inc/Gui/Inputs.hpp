#ifndef GUI_INPUTS_HPP
#define GUI_INPUTS_HPP

#include <array>
#include <Gui/ButtonState.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Gui
{

struct RawInputs
{
															RawInputs()
															{
																keyboard.fill(Button::RawState::Released);
																mouse.fill(Button::RawState::Released);
															}
	std::array<Button::RawState, sf::Keyboard::KeyCount>	keyboard;
	std::array<Button::RawState, sf::Mouse::ButtonCount>	mouse;
	sf::Vector2u 											cursor_position;
};	

// RawInputs::RawInputs()


struct Inputs
{
														Inputs()
														{
															keyboard.fill(Button::State::NotPressed);
															mouse.fill(Button::State::NotPressed);
														}
	std::array<Button::State, sf::Keyboard::KeyCount>	keyboard;
	std::array<Button::State, sf::Mouse::ButtonCount>	mouse;
	sf::Vector2u 										cursor_position;
};

// Inputs::Inputs()


} // namespace Gui

#endif // GUI_INPUTS_HPP