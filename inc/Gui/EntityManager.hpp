#ifndef GUI_ENTITY_MANAGER_HPP
#define GUI_ENTITY_MANAGER_HPP

#include <utility>
#include <vector>
#include <memory>
#include <SFML/System/Time.hpp>
#include <Gui/Entity.hpp>

namespace Gui
{

class EntityManager
{
using EntityVec = std::vector<std::unique_ptr<Entity>>;

public:
	void 			addEntity(std::unique_ptr<Entity>&& entity_) { _entities.emplace_back(std::move(entity_)); }
	const auto&		getEntities() const { return _entities; }
	void 			updateEntities(float delta_time_, const Inputs& inputs_);
	void			drawEntities(std::unique_ptr<sf::RenderWindow>& window_);

private:
	EntityVec 		_entities;
};

} // namespace Gui

#endif // GUI_ENTITY_MANAGER_HPP
