#include <Gui/RawInputReceiver.hpp>

namespace Gui
{

	void update_raw_inputs(RawInputs& raw_inputs_)
	{
		auto last_frame_raw_inputs{std::move(raw_inputs_)};

		for (auto button_idx{0u}; button_idx < sf::Mouse::ButtonCount; ++button_idx)
			if (last_frame_raw_inputs.mouse[button_idx].event == RawInputType::Event::Pressed)
				raw_inputs_.mouse[button_idx].state = RawInputType::State::Pressed;
			else if (last_frame_raw_inputs.mouse[button_idx].event == RawInputType::Event::Released)
				raw_inputs_.mouse[button_idx].state = RawInputType::State::Released;
	}

	void handle_direct_events(const sf::Event& event_, RawInputs& raw_inputs_)
	{
		if (event_.type == sf::Event::MouseMoved)
			raw_inputs_.cursor_position = {static_cast<unsigned>(event_.mouseMove.x), static_cast<unsigned>(event_.mouseMove.y)};
	}

	void handle_queued_events(const sf::Event& event_, RawInputs& raw_inputs_)
	{
		for (auto i{0}; i < sf::Keyboard::KeyCount; ++i)
		{
			// if (event_.type == sf::Event::KeyPressed && event_.key.code == i)
			// 	raw_inputs_.keyboard[i] = Raw::PressedThisFrame;
			// else if (event_.type == sf::Event::KeyReleased && event_.key.code == i)
			// 	raw_inputs_.keyboard[i] = Raw::ReleasedThisFrame;
			// else
			// {
			// 	if (last_frame_raw_inputs.keyboard[i] == Raw::PressedThisFrame)
			// 		raw_inputs_.keyboard[i] = Raw::Pressed;
			// 	else if (last_frame_raw_inputs.keyboard[i] == Raw::ReleasedThisFrame)
			// 		raw_inputs_.keyboard[i] = Raw::Released;
			// }
		}

		if (event_.type == sf::Event::MouseButtonPressed)
		{
			for (auto button_idx{0u}; button_idx < sf::Mouse::ButtonCount; ++button_idx)
				if (event_.mouseButton.button == button_idx && raw_inputs_.mouse[button_idx] != Raw::Pressed)
					raw_inputs_.mouse[button_idx] = Raw::PressedThisFrame;
		}
		else if (event_.type == sf::Event::MouseButtonReleased)
		{
			for (auto button_idx{0u}; button_idx < sf::Mouse::ButtonCount; ++button_idx)
				if (event_.mouseButton.button == button_idx && raw_inputs_.mouse[button_idx] != Raw::Released)
					raw_inputs_.mouse[button_idx] = Raw::ReleasedThisFrame;
		}
	}

	void RawInputReceiver::receiveInput(std::unique_ptr<sf::RenderWindow>& window_);
	{
		update_raw_inputs(_raw_inputs);

		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				_should_window_close = true;

			switch (event.type)
			{
				case sf::Event::KeyPressed:
				case sf::Event::KeyReleased:
				case sf::Event::MouseButtonPressed:
				case sf::Event::MouseButtonReleased:
				_unhandled_queued_events.emplace(event);
				
				default:
				handle_direct_events(event, _raw_inputs);
			}
		}

		std::clog << _unhandled_queued_events.size() << ' ';

		if (!_unhandled_queued_events.empty())
		{	
			handle_queued_events(_unhandled_queued_events.front(), _raw_inputs);
			_unhandled_queued_events.pop();
		}
	}
};