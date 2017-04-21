#include <catch.hpp>
#include <Directions.hpp>
#include <Grid.hpp>

using namespace Directions;

TEST_CASE("Grid")
{
	Grid grid{500, 6, 6};

	auto& test_cell{grid.getCells()[4]};

	SECTION("Neighbors")
	{
		REQUIRE(test_cell.getNeighbors()[West]->getNeighbors()[East] == test_cell.getNeighbors()[East]->getNeighbors()[West]);
	}

	SECTION("Walls")
	{
		REQUIRE(test_cell.getWalls()[North] == nullptr);
		REQUIRE(test_cell.getWalls()[South] == test_cell.getNeighbors()[South]->getWalls()[North]);
	}
}