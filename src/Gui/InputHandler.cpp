#include <utility>
#include <math.h>
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <Gui/Consts.hpp>
#include <Gui/InputHandler.hpp>

namespace Gui
{

bool within_threshold(sf::Vector2u vec_)
{
	return (std::pow(vec_.x, 2) + std::pow(vec_.y, 2) <= std::pow(cst::Input::threshold_drag, 2));
}

void InputHandler::handleInput(const RawInputs& raw_inputs_) // Translate RawInputs to Inputs
{
	for (auto button_idx{0}; button_idx < sf::Mouse::ButtonCount; ++button_idx)
	{
		if (raw_inputs_.mouse[button_idx].event == RawInputType::Event::Pressed)
		{
			_inputs._mouse[button_idx].event = MouseInputType::Event::Pressed;
			_inputs._mouse[button_idx].state = MouseInputType::State::Pressed;
			_inputs.pressed_down->cursor_position = raw_inputs_.cursor_position; // Save Cursor Position on Pressdown
		}
		
		if (raw_inputs_.mouse[button_idx].state == RawInputType::State::Released)
		{
			_inputs._mouse[button_idx].state = MouseInputType::State::Released;
		}
		else if (raw_inputs_.mouse[button_idx].state == RawInputType::State::Pressed && _inputs._mouse[button_idx].state != MouseInputType::State::Dragged)
		{
			if (within_threshold(raw_inputs_.cursor_position - _inputs.pressed_down->cursor_position))
				_inputs._mouse[button_idx].state = MouseInputType::State::Pressed;
			else
				_inputs._mouse[button_idx].state = MouseInputType::State::Dragged;
		}
		else if (raw_inputs_.mouse[button_idx].event == RawInputType::Event::Released)
		{
			if (_inputs._mouse[button_idx].state == MouseInputType::State::Dragged || (_inputs._mouse[button_idx].state == MouseInputType::State::Pressed
				&& !within_threshold(raw_inputs_.cursor_position - _inputs.pressed_down->cursor_position)))
				_inputs._mouse[button_idx].event = MouseInputType::Event::Dropped;
			else if (_inputs._mouse[button_idx].state == MouseInputType::State::Pressed || _inputs._mouse[button_idx].state == MouseInputType::State::Pressed)
				_inputs._mouse[button_idx].event = MouseInputType::Event::Clicked;

			_inputs.pressed_down = {}; // TODO: Replace with _inputs.pressed_down.reset() in C++17
		}
	}

	_inputs.cursor_position = raw_inputs_.cursor_position;
}

} // namespace Gui