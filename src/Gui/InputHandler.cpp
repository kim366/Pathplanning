#include <utility>
#include <math.h>
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <Gui/Consts.hpp>
#include <Gui/InputHandler.hpp>

namespace Gui
{

void reset_events(Inputs::MouseArr& mouse_, Inputs::KeyboardArr& keyboard_)
{
	for (auto& button : mouse_)
		button.event = MouseInputType::Event::None;

	for (auto& key : keyboard_)
		key.event = RawInputType::Event::None;
}

bool within_threshold(sf::Vector2u vec_)
{
	return (std::pow(vec_.x, 2) + std::pow(vec_.y, 2) <= std::pow(cst::Input::threshold_drag, 2));
}

void handle_mouse(RawInputs raw_inputs_, Inputs::MouseArr& mouse_)
{
	for (auto button_idx{0}; button_idx < sf::Mouse::ButtonCount; ++button_idx)
	{
		// States
		if (raw_inputs_.mouse[button_idx].state == RawInputType::State::Released) // Raw Released
		{
			mouse_[button_idx].state = MouseInputType::State::Released;
		}
		else if (raw_inputs_.mouse[button_idx].state == RawInputType::State::Pressed && mouse_[button_idx].state != MouseInputType::State::Dragged)
		{
			if (mouse_[button_idx].pressed_down_cursor_position
			&& within_threshold(raw_inputs_.cursor_position - *mouse_[button_idx].pressed_down_cursor_position)) // Raw Pressed
				mouse_[button_idx].state = MouseInputType::State::Pressed;
			else
				mouse_[button_idx].state = MouseInputType::State::Dragged;
		}

		// Events
		if (raw_inputs_.mouse[button_idx].event == RawInputType::Event::Pressed) // Raw Pressed
		{
			mouse_[button_idx].event = MouseInputType::Event::Pressed;
			mouse_[button_idx].pressed_down_cursor_position = raw_inputs_.cursor_position; // Save Cursor Position on Pressdown
		}
		else if (raw_inputs_.mouse[button_idx].event == RawInputType::Event::Released) // Raw Released
		{
			if (mouse_[button_idx].last_frame_state == MouseInputType::State::Dragged)
				mouse_[button_idx].event = MouseInputType::Event::Dropped;
			else
				mouse_[button_idx].event = MouseInputType::Event::Clicked;

			mouse_[button_idx].pressed_down_cursor_position = {}; // TODO: Replace with _mouse[button_idx].pressed_down_cursor_position.reset() in C++17
		}

		mouse_[button_idx].last_frame_state = mouse_[button_idx].state;
	}
}

void InputHandler::handleInput(const RawInputs& raw_inputs_) // Translate RawInputs to Inputs
{

	reset_events(_inputs._mouse, _inputs._keyboard);

	handle_mouse(raw_inputs_, _inputs._mouse);
	
	_inputs._keyboard = raw_inputs_.keyboard;

	_inputs.cursor_position = raw_inputs_.cursor_position;
}

} // namespace Gui