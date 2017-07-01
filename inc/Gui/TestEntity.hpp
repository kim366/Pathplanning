#ifndef GUI_TEST_ENTITY_CPP
#define GUI_TEST_ENTITY_CPP

#include <Gui/Entity.hpp>

namespace Gui
{

class TestEntity : public Entity
{
public:
	virtual void update(float delta_time_, const Inputs& inputs_) override;
	virtual void draw(sf::RenderTarget& target_, sf::RenderStates states_) const override {};

private:
	
};

} // namespace Gui

#endif // GUI_TEST_ENTITY_CPP