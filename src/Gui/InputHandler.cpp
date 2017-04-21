#include <Gui/InputHandler.hpp>
#include <SFML/Window/Event.hpp>
#include <utility>

namespace Gui
{

InputHandler::InputHandler(sf::RenderWindow& window_)
	: _window(window_)
{
}

void InputHandler::handleInput()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		auto last_frame_raw_inputs{std::move(_raw_inputs)};

		for (auto i{0}; i < sf::Keyboard::KeyCount; ++i)
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == i)
				_raw_inputs.keyboard[i] = Button::RawState::PressedThisFrame;
			else if (event.type == sf::Event::KeyReleased && event.key.code == i)
				_raw_inputs.keyboard[i] = Button::RawState::ReleasedThisFrame;
			else
			{
				if (_raw_inputs.keyboard[i] == Button::RawState::PressedThisFrame)
					_raw_inputs.keyboard[i] = Button::RawState::Pressed;
				if (_raw_inputs.keyboard[i] == Button::RawState::ReleasedThisFrame)
					_raw_inputs.keyboard[i] = Button::RawState::Released;
			}
		}
	}	
}

} // namespace Gui