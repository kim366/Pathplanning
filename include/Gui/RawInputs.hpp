#pragma once

#include <array>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <Gui/RawInputType.hpp>

namespace Gui
{

struct RawInputs
{
	using 					KeyboardArr = std::array<RawInputType::Button, sf::Keyboard::KeyCount>;
	using 					MouseArr = std::array<RawInputType::Button, sf::Mouse::ButtonCount>;

	KeyboardArr				keyboard;
	MouseArr				mouse;
	sf::Vector2u 			cursor_position;

};

} // namespace Gui


