#include <Grid.hpp>
#include <math.h>
#include <SFML/System/Vector2.hpp>
#include <Consts.hpp>
#include <Gui/Consts.hpp>

Grid::Grid(unsigned size_)
{
	_nodes.reserve(std::pow(size_, 2));

	float total_size{Gui::cst::Window::size - 2 * Gui::cst::Graph::node_radius};
	
	for (auto y_coordinate{0u}; y_coordinate < size_; ++y_coordinate)
	{
		for (auto x_coordinate{0u}; x_coordinate < size_; ++x_coordinate)
		{
			createNode({(x_coordinate / size_) * total_size, (y_coordinate / size_) * total_size});
		}
	}

	for (auto y_coordinate{0u}; y_coordinate < size_; ++y_coordinate)
	{
		for (auto x_coordinate{0u}; x_coordinate < size_; ++x_coordinate)
		{
			unsigned current_node_index{size_ * x_coordinate + y_coordinate};

			for (auto direction{0u}; direction < 4; ++direction)
			{
				unsigned neighbor_node_index{current_node_index};

				if (direction == 0)
					neighbor_node_index -= size_;
				else if (direction == 1)
					++neighbor_node_index;
				else if (direction == 2)
					neighbor_node_index += size_;
				else if (direction == 3)
					--neighbor_node_index;

				if (neighbor_node_index >= 0 && neighbor_node_index < _nodes.size())
				connect({current_node_index, neighbor_node_index});
			}
		}
	}
}
