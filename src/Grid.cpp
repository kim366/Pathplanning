#include <Directions.hpp>
#include <Grid.hpp>
#include <math.h>

Grid::Grid(float total_size_, unsigned number_of_cells_, float wall_width_)
	: _total_size(total_size_)
	, _number_of_cells(number_of_cells_)
	, _wall_width(wall_width_)
{
	_cells.reserve(std::pow(number_of_cells_, 2));
	_walls.reserve(2 * number_of_cells_ * (number_of_cells_ - 1));

	const float tile_size{(_total_size - (_number_of_cells - 1) * _wall_width) / _number_of_cells};

	for (int row_idx{0}; row_idx < number_of_cells_; ++row_idx)
	{
		for (int col_idx{0}; col_idx < number_of_cells_; ++col_idx)
		{
			float position{(tile_size + _wall_width) * row_idx};
			_cells.emplace_back(sf::FloatRect{{position, position}, {tile_size, tile_size}});
		}
	}

	for (int cell_idx{0}; cell_idx < _cells.size(); ++cell_idx)
	{
		Cell::NeighborArr neighbors;

		auto getneighbor{[&] (sf::Vector2i dir_) -> Cell*
		{
			return &_cells.at(cell_idx + dir_.x + _total_size * dir_.y);
		}};

		for (int neighbor_idx{0}; neighbor_idx < 8; ++neighbor_idx)
		{
			try { neighbors[neighbor_idx] = getneighbor(Directions::array[neighbor_idx]); }
			catch (const std::out_of_range&) { /* Everything ok */ }
		}

		_cells[cell_idx].setNeighbors(std::move(neighbors));
	}		
}

void Grid::draw(sf::RenderTarget& target_, sf::RenderStates states_) const
{

}