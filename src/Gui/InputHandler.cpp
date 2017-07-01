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

InputHandler::InputHandler(sf::RenderWindow& window_)
	: _window(window_)
{
}

void InputHandler::handleInput(const RawInputs& raw_inputs_)
{
	for (auto button_idx{0}; button_idx < sf::Mouse::ButtonCount; ++button_idx)
	{
		if (raw_inputs_.mouse[button_idx].event == RawInputType::Event::Pressed)
		{
			_inputs.mouse[button_idx] = Mse::Pressed;
			raw_inputs_.mouse_pressed_down->cursor_position = raw_inputs_.cursor_position;
		}
		else if (raw_inputs_.mouse[button_idx].state == RawInputType::State::Released)
			_inputs.mouse[button_idx] = Mse::NoAction;
		else if (raw_inputs_.mouse[button_idx].state == RawInputType::State::Pressed && _inputs.mouse[button_idx].state != MouseInputType::State::Dragged)
		{
			if (within_threshold(raw_inputs_.cursor_position - raw_inputs_.mouse_pressed_down->cursor_position))
				_inputs.mouse[button_idx] = MouseInputType::State::Held;
			else
				_inputs.mouse[button_idx] = MouseInputType::State::Dragged;
		}
		else if (raw_inputs_.mouse[button_idx].event == RawInputType::Event::Released)
		{
			if (_inputs.mouse[button_idx].state == MouseInputType::State::Dragged || (_inputs.mouse[button_idx].state == MouseInputType::State::Pressed
				&& !within_threshold(raw_inputs_.cursor_position - raw_inputs_.mouse_pressed_down->cursor_position)))
				_inputs.mouse[button_idx] = Mse::DragReleased;
			else if (_inputs.mouse[button_idx].state == MouseInputType::State::Held || _inputs.mouse[button_idx].state == MouseInputType::State::Pressed)
				_inputs.mouse[button_idx] = Mse::Clicked;

			raw_inputs_.mouse_pressed_down = {};
		}
	}

	_inputs.cursor_position = raw_inputs_.cursor_position;
}

} // namespace Gui