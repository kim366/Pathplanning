#include <Grid.hpp>
#include <math.h>
#include <SFML/System/Vector2.hpp>
#include <Consts.hpp>
#include <Gui/Consts.hpp>

Grid::Grid(unsigned size_, bool eight_connected_)
	: _size(size_)
{
	_nodes.reserve(std::pow(_size, 2));

	float total_size{Gui::cst::Window::size - 2 * Gui::cst::Graph::node_radius};
	
	for (auto y_coordinate{0u}; y_coordinate < _size; ++y_coordinate)
	{
		for (auto x_coordinate{0u}; x_coordinate < _size; ++x_coordinate)
		{
			createNode({(x_coordinate / _size) * total_size, (y_coordinate / _size) * total_size});
		}
	}

	for (auto y_coordinate{0u}; y_coordinate < _size; ++y_coordinate)
	{
		for (auto x_coordinate{0u}; x_coordinate < _size; ++x_coordinate)
		{
			unsigned current_node_index{toIndex({x_coordinate, y_coordinate})};

			for (auto direction{0u}; direction < (eight_connected_ ? 8 : 4); ++direction)
			{
				unsigned neighbor_node_index{current_node_index};

				if (direction == 0)
				{
					if (y_coordinate == 0)
						continue;
					neighbor_node_index -= _size;
				}
				else if (direction == 1)
				{
					if (x_coordinate == _size)
						continue;
					++neighbor_node_index;
				}
				else if (direction == 2)
				{
					if (y_coordinate == _size)
						continue;
					neighbor_node_index += _size;
				}
				else if (direction == 3)
				{
					if (x_coordinate == 0)
						continue;
					--neighbor_node_index;
				}
				else if (direction == 4)
				{
					if (x_coordinate == 0 ||
						y_coordinate == 0)
						continue;
					--neighbor_node_index -= _size;
				}
				else if (direction == 5)
				{
					if (x_coordinate == 0 ||
						y_coordinate == _size)
						continue;
					--neighbor_node_index += _size;
				}
				else if (direction == 6)
				{
					if (x_coordinate == _size ||
						y_coordinate == 0)
						continue;
					++neighbor_node_index -= _size;
				}
				else if (direction == 7)
				{
					if (x_coordinate == _size ||
						y_coordinate == _size)
						continue;
					++neighbor_node_index += _size;
				}

				if (neighbor_node_index < 0 || neighbor_node_index >= _nodes.size())
					continue;

				connect({current_node_index, neighbor_node_index});
			}
		}
	}
}

unsigned Grid::toIndex(sf::Vector2u coordinate_)
{
	return _size * coordinate_.y + coordinate_.x;
}

sf::Vector2u Grid::toCoordinate(int index_)
{
	unsigned x{0}, y{0};
	while (index_ >= static_cast<int>(_size))
	{
		index_ -= _size;
		++y;
	}

	x = index_;

	return {x, y};
}
