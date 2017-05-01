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
	explicit		EntityManager(const Inputs& inputs_) : _inputs(inputs_) {} 
	void 			addEntity(std::unique_ptr<Entity>&& entity_) { _entities.emplace_back(std::move(entity_)); }
	const auto&		getEntities() const { return _entities; }
	void 			updateEntities(float delta_time_);
	void			drawEntities(sf::RenderWindow& window_);

private:
	EntityVec 		_entities;
	const Inputs&	_inputs;
};

} // namespace Gui

#endif // GUI_ENTITY_MANAGER_HPP
