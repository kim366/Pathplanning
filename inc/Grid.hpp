#ifndef GRID_HPP
#define GRID_HPP

#include <Graph.hpp>

class Grid : public Graph
{
public:
					Grid(unsigned size_, bool eight_connected_ = false);
	unsigned		toIndex(sf::Vector2u coordinate_);
	sf::Vector2u	toCoordinate(int index_);

private:
	float 			_total_size;
	const unsigned	_size;

public:
	const bool		eight_connected;
	const unsigned	unit;
	const unsigned	diagonal_unit;
};

#endif // GRID_HPP