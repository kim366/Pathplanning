#ifndef GUI_INPUTS_HPP
#define GUI_INPUTS_HPP

#include <array>
#include <Gui/ButtonState.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <experimental/optional>

namespace Gui
{

struct RawInputs
{
private:
	struct PressDown
	{
		sf::Vector2u		cursor_position;
		sf::Mouse::Button 	button;
	};

public:
															RawInputs();
	std::array<Button::RawState, sf::Keyboard::KeyCount>	keyboard;
	std::array<Button::RawState, sf::Mouse::ButtonCount>	mouse;
	sf::Vector2u 											cursor_position;
	std::experimental::optional<PressDown>					mouse_pressed_down;	
};

struct Inputs
{
																Inputs();
	std::array<Button::State::Keyboard, sf::Keyboard::KeyCount>	keyboard;
	std::array<Button::State::Mouse, sf::Mouse::ButtonCount>	mouse;
	sf::Vector2u 												cursor_position;

};

} // namespace Gui

#endif // GUI_INPUTS_HPP