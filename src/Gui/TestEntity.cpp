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
		std::clog << "LMB pressed\t";
	if (inputs_.event.released(sf::Mouse::Left))
		std::clog << "LMB released\t";
	if (inputs_.event.dropped(sf::Mouse::Left))
		std::clog << "LMB dropped\t";
	if (inputs_.event.clicked(sf::Mouse::Left))
		std::clog << "LMB clicked\t";

	if (inputs_.state.released(sf::Mouse::Left))
		std::clog << "::LMB released\n";
	if (inputs_.state.pressed(sf::Mouse::Left) && !inputs_.state.dragged(sf::Mouse::Left))
		std::clog << "::LMB pressed\n";
	if (inputs_.state.dragged(sf::Mouse::Left))
		std::clog << "::LMB dragged\n";

}

void Gui::TestEntity::draw(sf::RenderTarget& target_, sf::RenderStates states_) const
{
	target_.draw(_shape, states_);
}