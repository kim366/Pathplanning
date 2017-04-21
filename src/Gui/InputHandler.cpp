#include <Gui/InputHandler.hpp>
#include <SFML/Window/Event.hpp>
#include <utility>

namespace Gui
{

bool close_window_if_necessary(const sf::Event& event_, sf::RenderWindow& window_)
{
	if (event_.type == sf::Event::Closed || (event_.type == sf::Event::KeyPressed && event_.key.code == sf::Keyboard::Escape))
		return true;
	else
		return false;
}

InputHandler::InputHandler(sf::RenderWindow& window_)
	: _window(window_)
{
}

bool InputHandler::handleInput()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if(close_window_if_necessary(event, _window))
			return true;

		auto last_frame_raw_inputs{std::move(_raw_inputs)};

		for (auto i{0}; i < sf::Keyboard::KeyCount; ++i)
		{
			using Raw = Button::RawState;

			if (event.type == sf::Event::KeyPressed && event.key.code == i)
				_raw_inputs.keyboard[i] = Raw::PressedThisFrame;
			else if (event.type == sf::Event::KeyReleased && event.key.code == i)
				_raw_inputs.keyboard[i] = Raw::ReleasedThisFrame;
			else
			{
				if (last_frame_raw_inputs.keyboard[i] == Raw::PressedThisFrame)
					_raw_inputs.keyboard[i] = Raw::Pressed;
				else if (last_frame_raw_inputs.keyboard[i] == Raw::ReleasedThisFrame)
					_raw_inputs.keyboard[i] = Raw::Released;
			}
		}
	}
	return false;
}

} // namespace Gui