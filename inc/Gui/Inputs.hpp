#ifndef GUI_INPUTS_HPP
#define GUI_INPUTS_HPP

#include <array>
#include <Gui/RawInputType.hpp>
#include <Gui/MouseInputType.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <experimental/optional>

namespace Gui
{

class Inputs
{
private:
	struct Event
	{
						Event(const Inputs& inputs_) : _inputs(inputs_) {}
		bool 			pressed(sf::Mouse::Button button_);
		bool			released(sf::Mouse::Button button_);
		bool 			dropped(sf::Mouse::Button button_);
		bool 			clicked(sf::Mouse::Button button_);

		bool 			pressed(sf::Keyboard::Key key_);
		bool 			released(sf::Keyboard::Key key_);

	private:
		const Inputs&	_inputs;
	};

	struct State
	{
						State(const Inputs& inputs_) : _inputs(inputs_) {}
		bool 			released(sf::Mouse::Button button_);
		bool 			pressed(sf::Mouse::Button button_);
		bool 			dragged(sf::Mouse::Button button_);
			
		bool 			pressed(sf::Keyboard::Key key_);
		bool 			released(sf::Keyboard::Key key_);

	private:
		const Inputs&	_inputs;
	};

public:
	using 			KeyboardArr = std::array<RawInputType::Button, sf::Keyboard::KeyCount>;
	using 			MouseArr 	= std::array<MouseInputType::Button, sf::Mouse::ButtonCount>;

	Event			event{*this};
	State 			state{*this};
	

	
private:	
	struct PressDown
	{
		sf::Vector2u		cursor_position;
		sf::Mouse::Button 	button;
	};

public:
	sf::Vector2u	cursor_position;
	std::experimental::optional<PressDown>
					pressed_down;

private:
	KeyboardArr		_keyboard;
	MouseArr		_mouse;

};

} // namespace Gui

#endif // GUI_INPUTS_HPP