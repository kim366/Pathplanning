#pragma once

#include <Graph.hpp>

class Grid : public Graph
{
public:
					Grid(unsigned size_, bool eight_connected_ = false);
	int				toIndex(sf::Vector2i coordinate_) const;
	sf::Vector2i	toCoordinate(int index_) const;

private:
	float 			_total_size;
	const unsigned	_size;

public:
	const bool		eight_connected;
	float			unit;
	float 			diagonal_unit;
};

