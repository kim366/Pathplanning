#include <iostream>
#include <catch.hpp>
#include <Grid.hpp>

SCENARIO("Four-connected graphs can be generated correctly")
{
	GIVEN("A 5x5 four-connected grid and some pointers to nodes")
	{
		Grid grid{5};

		Node* node_0_0{grid.getNode(0)};
		Node* node_1_2{grid.getNode(7)};
		Node* node_0_2{grid.getNode(2)};

		THEN("The nodes have the correct amount of connections")
		{
			REQUIRE(node_0_0->expand().size() == 2);
			REQUIRE(node_1_2->expand().size() == 4);
		}

		THEN("The correct nodes are connected")
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
}

SCENARIO("Eight-connected graphs can be generated correctly")
{
	GIVEN("A 5x5 eight-connected grid and some pointers to nodes")
	{
		Grid grid{5, true};

		Node* node_0_0{grid.getNode(0)};
		Node* node_1_2{grid.getNode(7)};
		Node* node_0_2{grid.getNode(2)};

		// for (auto i{0u}; i < 25; ++i)
		// 	std::cout << i << ":\t" << grid.getNode(i) << '\n'; 

		// for (auto& successor : node_0_0->expand())
		// 	std::cout << successor << ", ";
		
		THEN("The nodes have the correct amount of connections")
		{
			REQUIRE(node_0_0->expand().size() == 3);
			REQUIRE(node_1_2->expand().size() == 8);
			REQUIRE(node_0_2->expand().size() == 5);
		}

		THEN("The correct nodes are connected")
		{
				auto node_0_2_successors{node_0_2->expand()};
				REQUIRE(std::find(begin(node_0_2_successors), end(node_0_2_successors), node_1_2) != end(node_0_2_successors));

				auto node_1_2_successors{node_1_2->expand()};
				REQUIRE(std::find(begin(node_1_2_successors), end(node_1_2_successors), node_0_2) != end(node_1_2_successors));
		}
	}
}

SCENARIO("Index/Coordinate Conversion works")
{
	GIVEN("A 5x5 grid")
	{
		Grid grid{5};

		THEN("Conversion to Index works")
		{
			CHECK(grid.toIndex({3, 4}) == 23);
			CHECK(grid.toIndex({0, 0}) == 0);
			CHECK(grid.toIndex({3, 1}) == 8);	
		}

		THEN("Conversion to Coordinate works")
		{
			CHECK(grid.toCoordinate(9) == sf::Vector2u(4, 1));
			CHECK(grid.toCoordinate(17) == sf::Vector2u(2, 3));
			CHECK(grid.toCoordinate(20) == sf::Vector2u(0, 4));
		}
	}
}
