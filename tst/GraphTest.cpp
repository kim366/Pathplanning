#include <iterator>
#include <catch.hpp>
#include <Graph.hpp>

Graph graph;

SCENARIO("Graphs work properly")
{
	GIVEN("An empty Graph")
	{
		Graph graph;

		WHEN("Two Nodes get added to the Graph")
		{
			graph.createNode(50, 100);
			graph.createNode(10, 20);

			THEN("The graph records exactly two Nodes")
			{
				REQUIRE(graph.getNodes().size() == 2);
			}
		}

		WHEN("The two Nodes are connected")
		{	
			graph.createNode(50, 100);
			graph.createNode(10, 20);

			auto* node2{graph.getNodes()[1].get()}; 
			auto* node1{graph.getNodes()[0].get()}; 

			graph.connect(0, 1);

			THEN("The Graph has one Edge")
			{
				REQUIRE(graph.getEdges().size() == 1);
			}

			THEN("The Edge Weight is computed correctly")
			{
				REQUIRE(node1->getEdges().at(node2)->getWeight() == Approx(89.443f).epsilon(.01f));
			}

			THEN("Both Nodes have the same Edge to each other")
			{
				REQUIRE(node1->getEdges().size() == 1);
				REQUIRE(node2->getEdges().size() == 1);
				REQUIRE(node1->getEdges().at(node2) == node2->getEdges().at(node1));
			}

			THEN("The Edge has a Pointer to each Node")
			{
				REQUIRE(node1->getEdges().find(node2) != end(node1->getEdges()));
				REQUIRE(node2->getEdges().find(node1) != end(node1->getEdges()));
			}
		}

		WHEN("The Nodes are connected again in reverse order")
		{
			graph.createNode(50, 100);
			graph.createNode(10, 20);
			auto* node2{graph.getNodes()[1].get()}; 
			auto* node1{graph.getNodes()[0].get()}; 

			graph.connect(0, 1);
			graph.connect(1, 0);
				
			THEN("Nothing changes")
			{
				REQUIRE(node1->getEdges().at(node2)->getWeight() == Approx(89.443f).epsilon(.01f));

				REQUIRE(node1->getEdges().size() == 1);
				REQUIRE(node2->getEdges().size() == 1);
				REQUIRE(node1->getEdges().at(node2) == node2->getEdges().at(node1));

				REQUIRE(node1->getEdges().find(node2) != end(node1->getEdges()));
				REQUIRE(node2->getEdges().find(node1) != end(node1->getEdges()));
			}
		}

		WHEN("The Nodes are disconnected")
		{
			graph.createNode(50, 100);
			graph.createNode(10, 20);
			
			auto* node2{graph.getNodes()[1].get()}; 
			auto* node1{graph.getNodes()[0].get()}; 

			graph.connect(1, 0);
			graph.disconnect(0, 1);

			THEN("The Graph records no Edge")
			{
				REQUIRE(graph.getEdges().size() == 0);
			}

			THEN("The Nodes have no connected Edges")
			{
				REQUIRE(node1->getEdges().size() == 0);
				REQUIRE(node2->getEdges().size() == 0);
			}
		}

		WHEN("The Nodes are deleted")
		{
			graph.createNode(50, 100);
			graph.createNode(10, 20);

			graph.deleteNode(0);
			graph.deleteNode(0);

			THEN("The Graph has no contents")
			{
				CHECK(graph.getNodes().size() == 0);
				CHECK(graph.getEdges().size() == 0);
			}
		}
	}
}