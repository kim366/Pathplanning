#include <catch.hpp>
#include <Grid.hpp>

SCENARIO("Graphs can be generated correctly")
{
	GIVEN("A 5x5 grid and some pointers to nodes")
	{
		Grid grid{5};

		Node* node_0_0{grid.getNode(0)};
		Node* node_1_2{grid.getNode(7)};
		Node* node_0_2{grid.getNode(2)};

		WHEN("The grid gets generated")
		{
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
}