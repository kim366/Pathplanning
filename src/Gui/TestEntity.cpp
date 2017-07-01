#include <iostream>
#include <Gui/TestEntity.hpp>

void Gui::TestEntity::update(float delta_time_, const Inputs& inputs_)
{
	using Mse = Button::State::Mouse;
	switch (inputs_.mouse[sf::Mouse::Left])
	{
		case Mse::NoAction: 	std::clog << "No Action"; 		break;
		case Mse::Pressed: 		std::clog << "Pressed"; 		break;
		case Mse::Held: 		std::clog << "Held"; 			break;
		case Mse::Clicked: 		std::clog << "Clicked"; 		break;
		case Mse::Dragged: 		std::clog << "Dragged"; 		break;
		case Mse::DragReleased: std::clog << "Drag Released"; 	break;
	}
	
	std::clog << '\n';

	// std::clog << "(" << inputs_.cursor_position.x << ", " << inputs_.cursor_position.y << ")\n";
}