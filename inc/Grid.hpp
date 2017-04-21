#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <Gui/Consts.hpp>
#include <Consts.hpp>
#include <Wall.hpp>
#include <Cell.hpp>

class Grid : sf::Drawable
{
public:
					Grid(float total_size_, unsigned number_of_cells_, float wall_width_);
	virtual void 	draw(sf::RenderTarget& target_, sf::RenderStates states_) const override;
	const auto&		getCells() { return _cells; };
	const auto&		getWalls() { return _walls; };

private:
	float 			_total_size{Gui::cst::Window::size};
	unsigned		_number_of_cells{cst::Grid::number_of_cells};
	float			_wall_width{cst::Grid::wall_width};
	std::vector<Wall>
					_walls;
	std::vector<Cell>
					_cells;
};

#endif // GRID_HPP