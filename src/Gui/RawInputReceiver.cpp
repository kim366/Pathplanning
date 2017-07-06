#include <Gui/RawInputReceiver.hpp>

namespace Gui
{
	bool should_window_close(const sf::Event& event_)
	{
		return (event_.type == sf::Event::Closed || (event_.type == sf::Event::KeyPressed && event_.key.code == sf::Keyboard::Escape));	 
	}

	void pop_queued_tactile_events(RawInputs& raw_inputs_)
	{
		auto last_frame_raw_inputs{std::move(raw_inputs_)};

		for (auto button_idx{0u}; button_idx < sf::Mouse::ButtonCount; ++button_idx)
		{
			if (last_frame_raw_inputs.mouse[button_idx].queued_tactile_event)
				raw_inputs_.mouse[button_idx].event = *last_frame_raw_inputs.mouse[button_idx].queued_tactile_event;
		}
	}

	void handle_other_events(const sf::Event& event_, RawInputs& raw_inputs_)
	{
		if (event_.type == sf::Event::MouseMoved)
			raw_inputs_.cursor_position = {static_cast<unsigned>(event_.mouseMove.x), static_cast<unsigned>(event_.mouseMove.y)};
	}

	void handle_tactile_events(const sf::Event& event_, RawInputs& raw_inputs_, bool second_of_frame)
	{
		// Short Hand
		auto& mouse_button{raw_inputs_.mouse[event_.mouseButton.button]};
		auto& key{raw_inputs_.keyboard[event_.key.code]};

		if (event_.type == sf::Event::MouseButtonPressed)
		{
			if (mouse_button.event == RawInputType::Event::None) // No event this frame yet
			{
				mouse_button.event = RawInputType::Event::Pressed;
				mouse_button.state = RawInputType::State::Pressed;
			}
			else if (!mouse_button.queued_tactile_event) // There has been another tactile event this frame
				mouse_button.queued_tactile_event = event_.type;
			// else case: four tactile events within 2 frames -- seems impossible; if problematic, fix by substituting optional with queue
		}
		else if (event_.type == sf::Event::MouseButtonReleased)
		{
			if (mouse_button.event == RawInputType::Event::None)
			{
				mouse_button.event = RawInputType::Event::Released;
				mouse_button.state = RawInputType::State::Released;
			}
			else if (!mouse_button.queued_tactile_event)
				mouse_button.queued_tactile_event = event_.type;
		}
		else if (event_.type == sf::Event::KeyPressed)
		{
			if (key.event == RawInputType::Event::None)
			{
				key.event = RawInputType::Event::Released;
				key.state = RawInputType::State::Released;
			}
			else if (!key.queued_tactile_event)
				key.queued_tactile_event = event_.type;
		}
		else if (event_.type == sf::Event::KeyReleased)
		{
			if (key.event == RawInputType::Event::None)
			{
				key.event = RawInputType::Event::Released;
				key.state = RawInputType::State::Released;
			}
			else if (!key.queued_tactile_event)
				key.queued_tactile_event = event_.type;
		}
	}

	void RawInputReceiver::receiveInput(std::unique_ptr<sf::RenderWindow>& window_)
	{
		for ()
		pop_queued_tactile_events(_raw_inputs);

		sf::Event event;
		while (window_->pollEvent(event))
		{
			_should_window_close = should_window_close(event);

			bool second_of_frame{false}; // Has an event been triggered on this Event this frame already?

			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
			{
				if (raw_inputs_.keyboard[event_.key.code].event != RawInputType::Event::None)
					second_of_frame = true;
				handle_tactile_events(event, _raw_inputs, second_of_frame);
			}
			else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
			{
				if (raw_inputs_.mouse[event_.mouseButton.button].event != RawInputType::Event::None)
					second_of_frame = true;
				handle_tactile_events(event, _raw_inputs, second_of_frame);
			}
			else
				handle_other_events(event, _raw_inputs);
		}
	}
};