#include <Cell.hpp>

Cell::Cell(sf::FloatRect rect_)
	: _rectangle({rect_.width, rect_.height})
{
	_neighbors.fill(nullptr);
	_walls.fill(nullptr);
	_rectangle.setPosition(rect_.left, rect_.top);
}

void Cell::setNeighbors(NeighborArr&& neighbors_)
{
	_neighbors = std::move(neighbors_); 
}

void Cell::setWalls(WallArr&& walls_)
{
	_walls = std::move(walls_); 
}

void Cell::update(float delta_time_, const Gui::Inputs& inputs_)
{

}

void Cell::draw(sf::RenderTarget& target_, sf::RenderStates states_) const
{
	
}