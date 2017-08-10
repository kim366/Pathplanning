#ifndef GRID_HPP
#define GRID_HPP

#include <Graph.hpp>

class Grid : public Graph
{
public:
					Grid(unsigned size_, bool eight_connected_ = false);

private:
	unsigned		toIndex(sf::Vector2u coordinate_);
	sf::Vector2u	toCoordinate(unsigned index_);

private:
	sf::Vector2u 	_size;
};

#endif // GRID_HPP