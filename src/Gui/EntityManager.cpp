#include <SFML/Graphics/RenderWindow.hpp>
#include <Gui/EntityManager.hpp>

void Gui::EntityManager::updateEntities(float delta_time_, const Inputs& inputs_)
{
	for (auto& entity : _entities)
		entity->update(delta_time_, inputs_);
}

void Gui::EntityManager::drawEntities(std::unique_ptr<sf::RenderWindow>& window_)
{
	window_->clear();
	for (auto& entity : _entities)
		window_->draw(*entity);
	window_->display();
}
