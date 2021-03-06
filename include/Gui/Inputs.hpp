#pragma once

#include <array>
#include <Gui/RawInputType.hpp>
#include <Gui/MouseInputType.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <optional>

namespace Gui
{

class Inputs
{
	friend class InputHandler;

private:
	struct Event
	{
						Event(const Inputs& inputs_) : _inputs(inputs_) {}
		bool 			pressed(sf::Mouse::Button button_) const;
		bool			released(sf::Mouse::Button button_) const;
		bool 			dropped(sf::Mouse::Button button_) const;
		bool 			clicked(sf::Mouse::Button button_) const;

		bool 			pressed(sf::Keyboard::Key key_) const;
		bool 			released(sf::Keyboard::Key key_) const;

	private:
		const Inputs&	_inputs;
	};

	struct State
	{
						State(const Inputs& inputs_) : _inputs(inputs_) {}
		bool 			released(sf::Mouse::Button button_) const;
		bool 			pressed(sf::Mouse::Button button_) const;
		bool 			dragged(sf::Mouse::Button button_) const;
			
		bool 			pressed(sf::Keyboard::Key key_) const;
		bool 			released(sf::Keyboard::Key key_) const;

	private:
		const Inputs&	_inputs;
	};

public:
	using 			KeyboardArr = std::array<RawInputType::Button, sf::Keyboard::KeyCount>;
	using 			MouseArr 	= std::array<MouseInputType::Button, sf::Mouse::ButtonCount>;

	Event			event{*this};
	State 			state{*this};

public:
	sf::Vector2u	cursor_position;

private:
	KeyboardArr		_keyboard;
	MouseArr		_mouse;

};

} // namespace Gui


