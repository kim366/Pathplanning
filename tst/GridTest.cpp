#include <iostream>
#include <catch.hpp>
#include <Grid.hpp>

TEST_CASE("Four-connected graphs")
{
	Grid grid{5};

	const Node* node_0_0{grid.getNode(grid.toIndex({0, 0}))};
	const Node* node_1_2{grid.getNode(grid.toIndex({1, 2}))};
	const Node* node_0_2{grid.getNode(grid.toIndex({0, 2}))};
	const Node* node_4_4{grid.getNode(grid.toIndex({4, 4}))};

	SECTION("The nodes have the correct amount of connections")
	{
		REQUIRE(node_0_0->expand().size() == 2);
		REQUIRE(node_1_2->expand().size() == 4);
		REQUIRE(node_0_2->expand().size() == 3);
		REQUIRE(node_4_4->expand().size() == 2);
	}

	SECTION("The correct nodes are connected")
	{
		{
			auto successors{node_0_2->expand()};
			REQUIRE(std::find(begin(successors), end(successors), node_1_2) != end(successors));
		}

		{
			auto successors{node_1_2->expand()};
			REQUIRE(std::find(begin(successors), end(successors), node_0_2) != end(successors));
		}
	}
}

SCENARIO("Eight-connected graphs")
{
	Grid grid{5, true};

	const Node* node_0_0{grid.getNode(grid.toIndex({0, 0}))};
	const Node* node_1_2{grid.getNode(grid.toIndex({1, 2}))};
	const Node* node_0_2{grid.getNode(grid.toIndex({0, 2}))};
	const Node* node_4_4{grid.getNode(grid.toIndex({4, 4}))};

	SECTION("The nodes have the correct amount of connections")
	{
		REQUIRE(node_0_0->expand().size() == 3);
		REQUIRE(node_1_2->expand().size() == 8);
		REQUIRE(node_0_2->expand().size() == 5);
		REQUIRE(node_4_4->expand().size() == 3);

	}

	SECTION("The correct nodes are connected")
	{
			auto node_0_2_successors{node_0_2->expand()};
			REQUIRE(std::find(begin(node_0_2_successors), end(node_0_2_successors), node_1_2) != end(node_0_2_successors));

			auto node_1_2_successors{node_1_2->expand()};
			REQUIRE(std::find(begin(node_1_2_successors), end(node_1_2_successors), node_0_2) != end(node_1_2_successors));
	}
}

TEST_CASE("Index/Coordinate Conversion")
{
	Grid grid{5};

	SECTION("Conversion to Index")
	{
		CHECK(grid.toIndex({3, 4}) == 23);
		CHECK(grid.toIndex({0, 0}) == 0);
		CHECK(grid.toIndex({0, 2}) == 10);
		CHECK(grid.toIndex({3, 1}) == 8);	
	}

	SECTION("Conversion to Coordinate")
	{
		CHECK(grid.toCoordinate(9) == sf::Vector2u(4, 1));
		CHECK(grid.toCoordinate(17) == sf::Vector2u(2, 3));
		CHECK(grid.toCoordinate(20) == sf::Vector2u(0, 4));
	}
}
