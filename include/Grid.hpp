#pragma once

#include <Graph.hpp>

class Grid : public Graph
{
public:
					Grid(unsigned size_, bool eight_connected_ = false, std::optional<int> seed_ = {});
	int				toIndex(sf::Vector2i coordinate_) const;
	sf::Vector2i	toCoordinate(int index_) const;
	void 			disconnectCrossingEges();

private:
	float 			_total_size;
	const unsigned	_size;

public:
	const bool		eight_connected;
	float			unit;
	float 			diagonal_unit;
};

