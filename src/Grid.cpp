#include <Grid.hpp>
#include <math.h>
#include <SFML/System/Vector2.hpp>
#include <Gui/Consts.hpp>
#include <random>

Grid::Grid(unsigned size_, bool eight_connected_, std::optional<int> seed_)
	: Graph{seed_}
	, _size{size_}
	, eight_connected{eight_connected_}
	, unit{_total_size / (_size - 1)}
	, diagonal_unit{eight_connected_ ? std::hypot(unit, unit) : 0}
{
	_node_radius = -(3 / 8.f) * size_ + (95 / 4.f);
	_total_size = Gui::cst::Window::size - 2 * _node_radius;

	_nodes.reserve(std::pow(_size, 2));
	
	for (int y_coordinate{0}; y_coordinate < _size; ++y_coordinate)
	{
		for (int x_coordinate{0}; x_coordinate < _size; ++x_coordinate)
		{
			float x_window_coordinate{(static_cast<float>(x_coordinate) / (_size - 1)) * _total_size + _node_radius};
			float y_window_coordinate{(static_cast<float>(y_coordinate) / (_size - 1)) * _total_size + _node_radius};
			createNode({x_window_coordinate, y_window_coordinate});
		}
	}

	for (int y_coordinate{0}; y_coordinate < _size; ++y_coordinate)
	{
		for (int x_coordinate{0}; x_coordinate < _size; ++x_coordinate)
		{	
			int current_node_index{toIndex({x_coordinate, y_coordinate})};

			for (int direction{0}; direction < (eight_connected_ ? 8 : 4); ++direction)
			{
				int neighbor_node_index{current_node_index};

				if (direction == 0)
				{
					if (y_coordinate == 0)
						continue;
					neighbor_node_index -= _size;
				}
				else if (direction == 1)
				{
					if (x_coordinate == _size - 1)
						continue;
					++neighbor_node_index;
				}
				else if (direction == 2)
				{
					if (y_coordinate == _size - 1)
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
						y_coordinate == _size - 1)
						continue;
					--neighbor_node_index += _size;
				}
				else if (direction == 6)
				{
					if (x_coordinate == _size - 1 ||
						y_coordinate == 0)
						continue;
					++neighbor_node_index -= _size;
				}
				else if (direction == 7)
				{
					if (x_coordinate == _size - 1 ||
						y_coordinate == _size - 1)
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

int Grid::toIndex(sf::Vector2i coordinate_) const
{
	return _size * coordinate_.y + coordinate_.x;
}

sf::Vector2i Grid::toCoordinate(int index_) const
{
	int x{0}, y{0};
	while (index_ >= static_cast<int>(_size))
	{
		index_ -= _size;
		++y;
	}

	x = index_;

	return {x, y};
}

void Grid::disconnectCrossingEges()
{
	std::mt19937 rng{std::random_device{}()};
	if (_seed)
		rng.seed(*_seed);

	for (int node_index = 0; node_index < _nodes.size() - _size - 1; ++node_index)
	{
		if (toCoordinate(node_index).x == _nodes.size() - 1)
			continue;

		int random{std::uniform_int_distribution{0, 1}(rng)};
		disconnect({node_index + random, toIndex(toCoordinate(node_index) + sf::Vector2i{1 - random, 1})});
	}
}
