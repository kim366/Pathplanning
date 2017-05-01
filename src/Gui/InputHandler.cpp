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

bool close_window_if_necessary(const sf::Event& event_, sf::RenderWindow& window_)
{
	if (event_.type == sf::Event::Closed || (event_.type == sf::Event::KeyPressed && event_.key.code == sf::Keyboard::Escape))
		return true;
	else
		return false;
}

void process_raw_inputs(const sf::Event& event_, RawInputs& raw_inputs_)
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
}

void process_inputs(RawInputs& raw_inputs_, Inputs& inputs_)
{
	for (auto button_idx{0}; button_idx < sf::Mouse::ButtonCount; ++button_idx)
	{
		using Key = Button::State::Keyboard;
		using Raw = Button::RawState;
		using Mse = Button::State::Mouse;

		if (raw_inputs_.mouse[button_idx] == Raw::PressedThisFrame)
		{
			inputs_.mouse[button_idx] = Mse::Pressed;
			raw_inputs_.mouse_pressed_down->cursor_position = raw_inputs_.cursor_position;
		}
		else if (raw_inputs_.mouse[button_idx] == Raw::Released)
			inputs_.mouse[button_idx] = Mse::NoAction;
		else if (raw_inputs_.mouse[button_idx] == Raw::Pressed && inputs_.mouse[button_idx] != Mse::Dragged)
		{
			if (within_threshold(raw_inputs_.cursor_position - raw_inputs_.mouse_pressed_down->cursor_position))
				inputs_.mouse[button_idx] = Mse::Held;
			else
				inputs_.mouse[button_idx] = Mse::Dragged;

		}
		else if (raw_inputs_.mouse[button_idx] == Raw::ReleasedThisFrame)
		{
			if (inputs_.mouse[button_idx] == Mse::Dragged)
				inputs_.mouse[button_idx] = Mse::DragReleased;
			else if (inputs_.mouse[button_idx] == Mse::Held)
				inputs_.mouse[button_idx] = Mse::Clicked;

			raw_inputs_.mouse_pressed_down = {};
		}
	}

	inputs_.cursor_position = raw_inputs_.cursor_position;
}

InputHandler::InputHandler(sf::RenderWindow& window_)
	: _window(window_)
{
}

bool InputHandler::handleInput()
{
	using Raw = Button::RawState;
	using Mse = Button::State::Mouse;
	using Raw = Button::RawState;

	auto last_frame_raw_inputs{std::move(_raw_inputs)};

	for (auto button_idx{0u}; button_idx < sf::Mouse::ButtonCount; ++button_idx)
	{
		if (last_frame_raw_inputs.mouse[button_idx] == Raw::PressedThisFrame)
		{
			_raw_inputs.mouse[button_idx] = Raw::Pressed;
		}
		else if (last_frame_raw_inputs.mouse[button_idx] == Raw::ReleasedThisFrame)
			_raw_inputs.mouse[button_idx] = Raw::Released;
	}

	sf::Event event;
	while (_window.pollEvent(event))
	{
		if(close_window_if_necessary(event, _window))
			return true;

		if (event.type == sf::Event::MouseButtonPressed)
		{
			for (auto button_idx{0u}; button_idx < sf::Mouse::ButtonCount; ++button_idx)
				if (event.mouseButton.button == button_idx && _raw_inputs.mouse[button_idx] != Raw::Pressed)
					_raw_inputs.mouse[button_idx] = Raw::PressedThisFrame;
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			for (auto button_idx{0u}; button_idx < sf::Mouse::ButtonCount; ++button_idx)
				if (event.mouseButton.button == button_idx && _raw_inputs.mouse[button_idx] != Raw::Released)
					_raw_inputs.mouse[button_idx] = Raw::ReleasedThisFrame;
		}
		else if (event.type == sf::Event::MouseMoved)
			_raw_inputs.cursor_position = {static_cast<unsigned>(event.mouseMove.x), static_cast<unsigned>(event.mouseMove.y)};
	}

	process_inputs(_raw_inputs, _inputs);

	return false;
}

} // namespace Gui