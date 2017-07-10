#ifndef GUI_TEST_ENTITY_CPP
#define GUI_TEST_ENTITY_CPP

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
	virtual void 	update(float delta_time_, const Inputs& inputs_) override;
	virtual void 	draw(sf::RenderTarget& target_, sf::RenderStates states_) const override;	
};

} // namespace Gui

#endif // GUI_TEST_ENTITY_CPP