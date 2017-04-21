#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <array>
#include <Gui/Entity.hpp>
#include <Wall.hpp>
#include <Gui/Inputs.hpp>

class Cell : public Gui::Entity
{

public:
using NeighborArr = std::array<const Cell*, 8>;
using WallArr = std::array<const Wall*, 4>;
						Cell(sf::FloatRect rect_);
	void				setNeighbors(NeighborArr&& neigbours_);
	void				setWalls(WallArr&& walls_);
	const auto&			getNeighbors() const { return _neighbors; }
	const auto&			getWalls() const { return _walls; }
	virtual void		update(float delta_time_, const Gui::Inputs& inputs_) override;
	virtual void		draw(sf::RenderTarget& target_, sf::RenderStates states_) const override;

private:
	sf::RectangleShape 	_rectangle;
	NeighborArr			_neighbors;
	WallArr				_walls;				
};

#endif // CELL_HPP