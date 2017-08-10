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
	bool			isOnEdge(unsigned index_, int direction_);

private:
	unsigned	 	_size;
};

#endif // GRID_HPP