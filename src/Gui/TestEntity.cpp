#include <iostream>
#include <Gui/TestEntity.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Gui::TestEntity::TestEntity()
{
	_shape.setFillColor(sf::Color::Green);
}

void Gui::TestEntity::update(float delta_time_, const Inputs& inputs_)
{
	if (inputs_.event.pressed(sf::Mouse::Left))
		std::clog << "LMB pressed\n";

	// std::clog << "(" << inputs_.cursor_position.x << ", " << inputs_.cursor_position.y << ")\n";
}

void Gui::TestEntity::draw(sf::RenderTarget& target_, sf::RenderStates states_) const
{
	target_.draw(_shape, states_);
}