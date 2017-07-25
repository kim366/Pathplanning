#include <catch.hpp>
#include <Graph.hpp>

Graph graph;

SCENARIO("Graphs work properly")
{
	Given("An empty Graph")
	{
		Graph graph;

		WHEN("Two Nodes are created and connected")
		{	
			auto* node1{graph.createNode(50, 100)};
			auto* node2{graph.createNode(10, 20)};
			graph.connect(node1, node2);

			THEN("The Edge Weight is computed correctly")
			{
				REQUIRE(graph.getWeight(node1, node2) == Approx(89.443f).epsilon(.01f));
			}
		}
	}
}