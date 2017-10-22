#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Gui/Inputs.hpp>

class EntityManager;

namespace Gui
{

class Entity : sf::Drawable
{
	friend class EntityManager;

protected:
	void 			draw(sf::RenderTarget& target_, sf::RenderStates states_) const override;	
	virtual void 	update(float delta_time_, const Inputs& inputs_) = 0;

public:
	~Entity() = 0;
};

} // namespace Gui


