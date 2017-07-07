#include <Gui/Inputs.hpp>

bool Gui::Inputs::State::pressed(sf::Mouse::Button button_) const
{
	return (_inputs._mouse[button_].state == MouseInputType::State::Pressed || _inputs._mouse[button_].state == MouseInputType::State::Dragged);
}

bool Gui::Inputs::State::released(sf::Mouse::Button button_) const
{
	return _inputs._mouse[button_].state == MouseInputType::State::Released;
}

bool Gui::Inputs::State::dragged(sf::Mouse::Button button_) const
{
	return (_inputs._mouse[button_].state == MouseInputType::State::Dragged || _inputs._mouse[button_].event == MouseInputType::Event::Dropped);
}

bool Gui::Inputs::Event::dropped(sf::Mouse::Button button_) const
{
	return _inputs._mouse[button_].event == MouseInputType::Event::Dropped;
}

bool Gui::Inputs::Event::clicked(sf::Mouse::Button button_) const
{
	return _inputs._mouse[button_].event == MouseInputType::Event::Clicked;
}

bool Gui::Inputs::Event::pressed(sf::Mouse::Button button_) const
{
	return _inputs._mouse[button_].event == MouseInputType::Event::Pressed;
}

bool Gui::Inputs::Event::released(sf::Mouse::Button button_) const
{
	return (_inputs._mouse[button_].event == MouseInputType::Event::Dropped || _inputs._mouse[button_].event == MouseInputType::Event::Clicked);
}

bool Gui::Inputs::State::pressed(sf::Keyboard::Key key_) const
{
	return _inputs._mouse[key_].state == MouseInputType::State::Pressed;
}

bool Gui::Inputs::State::released(sf::Keyboard::Key key_) const
{
	return _inputs._keyboard[key_].state == RawInputType::State::Released;
}

bool Gui::Inputs::Event::pressed(sf::Keyboard::Key key_) const
{
	return _inputs._keyboard[key_].event == RawInputType::Event::Pressed;
}

bool Gui::Inputs::Event::released(sf::Keyboard::Key key_) const
{
	return _inputs._keyboard[key_].event == RawInputType::Event::Released;
}