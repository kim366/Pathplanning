#include <iostream>
#include <Gui/TestEntity.hpp>

void Gui::TestEntity::update(float delta_time_, const Inputs& inputs_)
{
	if (inputs_.event.pressed(sf::Mouse::Left))
		std::clog << "LMB pressed\n";

	// std::clog << "(" << inputs_.cursor_position.x << ", " << inputs_.cursor_position.y << ")\n";
}