#include <Gui/RawInputReceiver.hpp>

namespace Gui
{
	void reset_events(RawInputs& raw_inputs_)
	{
		for (auto& button : raw_inputs_.mouse)
			button.event = RawInputType::Event::None;

		for (auto& key : raw_inputs_.keyboard)
			key.event = RawInputType::Event::None;
	}

	bool should_window_close(const sf::Event& event_)
	{
		return (event_.type == sf::Event::Closed || (event_.type == sf::Event::KeyPressed && event_.key.code == sf::Keyboard::Escape));	 
	}

	void handle_other_events(const sf::Event& event_, RawInputs& raw_inputs_)
	{
		if (event_.type == sf::Event::MouseMoved)
			raw_inputs_.cursor_position = {static_cast<unsigned>(event_.mouseMove.x), static_cast<unsigned>(event_.mouseMove.y)};
	}

	void handle_tactile_events(const sf::Event& event_, RawInputs& raw_inputs_)
	{
		// Short Hand
		auto& mouse_button{raw_inputs_.mouse[event_.mouseButton.button]};
		auto& key{raw_inputs_.keyboard[event_.key.code]};

		if (event_.type == sf::Event::MouseButtonPressed)
		{
			mouse_button.event = RawInputType::Event::Pressed;
			mouse_button.state = RawInputType::State::Pressed;
		}
		else if (event_.type == sf::Event::MouseButtonReleased)
		{
			mouse_button.event = RawInputType::Event::Released;
			mouse_button.state = RawInputType::State::Released;
		}
		else if (event_.type == sf::Event::KeyPressed)
		{
			key.event = RawInputType::Event::Pressed;
			key.state = RawInputType::State::Pressed;
		}
		else if (event_.type == sf::Event::KeyReleased)
		{
			key.event = RawInputType::Event::Released;
			key.state = RawInputType::State::Released;
		}
	}

	void RawInputReceiver::receiveInput(std::unique_ptr<sf::RenderWindow>& window_)
	{
		reset_events(_raw_inputs);

		sf::Event event;
		while (window_->pollEvent(event))
		{
			_should_window_close = should_window_close(event);

			switch (event.type)
			{
				case sf::Event::KeyPressed:
				case sf::Event::KeyReleased:
				case sf::Event::MouseButtonPressed:
				case sf::Event::MouseButtonReleased:
				handle_tactile_events(event, _raw_inputs);
				break;

				default:
				handle_other_events(event, _raw_inputs);
			}				
		}
	}
};