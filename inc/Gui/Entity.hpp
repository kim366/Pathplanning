#ifndef GUI_ENTITY_HPP
#define GUI_ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <Gui/Inputs.hpp>

class EntityManager;

namespace Gui
{

class Entity : sf::Drawable
{
	friend class EntityManager;

	virtual void update(float delta_time_, const Inputs& inputs_) = 0;
	virtual void draw(sf::RenderTarget& target_, sf::RenderStates states_) const override = 0;
};

} // namespace Gui

#endif // GUI_ENTITY_HPP