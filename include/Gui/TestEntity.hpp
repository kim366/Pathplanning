#pragma once

#include <Gui/Entity.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace Gui
{

class TestEntity : public Entity
{
public:
					TestEntity();

private:
	sf::CircleShape _shape{100.f};

private:
	void 			update(float delta_time_, const Inputs& inputs_) override;
	void 			draw(sf::RenderTarget& target_, sf::RenderStates states_) const override;	
};

} // namespace Gui


