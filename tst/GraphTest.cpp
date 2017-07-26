#include <iterator>
#include <catch.hpp>
#include <Graph.hpp>

Graph graph;

SCENARIO("Graphs work properly")
{
	GIVEN("An empty Graph and two empty Node pointers")
	{
		Graph graph;
		Node* node1;
		Node* node2; 

		WHEN("Two nodes get added to the Graph")
		{
			node1 = graph.createNode(50, 100);
			node2 = graph.createNode(10, 20);

			THEN("The graph records exactly two Nodes")
			{
				REQUIRE(graph.getNodes().size() == 2);
			}
		}

		WHEN("The two Nodes are connected")
		{	
			node1 = graph.createNode(50, 100);
			node2 = graph.createNode(10, 20);
			graph.connect(node1, node2);

			THEN("The Graph has one Edge")
			{
				REQUIRE(graph.getEdges().size() == 1);
			}

			THEN("The Edge Weight is computed correctly")
			{
				REQUIRE(graph.getWeight(node1, node2) == Approx(89.443f).epsilon(.01f));
			}

			THEN("Both nodes have the same edge Edge to each other")
			{
				REQUIRE(node1->edges.size() == 1);
				REQUIRE(node2->edges.size() == 1);
				REQUIRE(node1->edges[node2] == node2->edges[node1]);
			}

			THEN("The Edge has a Pointer to each Node")
			{
				REQUIRE(node1->edges.find(node2) != end(node1->edges));
				REQUIRE(node2->edges.find(node1) != end(node1->edges));
			}
		}

		WHEN("The nodes are connected again in reverse order")
		{
			node1 = graph.createNode(50, 100);
			node2 = graph.createNode(10, 20);
			graph.connect(node1, node2);
			graph.connect(node2, node1);
				
			THEN("Nothing changes")
			{
				REQUIRE(graph.getWeight(node1, node2) == Approx(89.443f).epsilon(.01f));

				REQUIRE(node1->edges.size() == 1);
				REQUIRE(node2->edges.size() == 1);
				REQUIRE(node1->edges[node2] == node2->edges[node1]);

				REQUIRE(node1->edges.find(node2) != end(node1->edges));
				REQUIRE(node2->edges.find(node1) != end(node1->edges));
			}
		}

		WHEN("The Nodes are disconnected")
		{
			node1 = graph.createNode(50, 100);
			node2 = graph.createNode(10, 20);
			graph.connect(node2, node1);
			graph.disconnect(node1, node2);

			THEN("The Graph records no Edge")
			{
				REQUIRE(graph.getEdges().size() == 0);
			}

			THEN("The Nodes have no connected Edges")
			{
				REQUIRE(node1->edges.size() == 0);
				REQUIRE(node2->edges.size() == 0);
			}
		}

		WHEN("The Nodes are deleted")
		{
			node1 = graph.createNode(50, 100);
			node2 = graph.createNode(10, 20);
			graph.deleteNode(node1);
			graph.deleteNode(node2);

			THEN("The Graph has no contents")
			{
				CHECK(graph.getNodes().size() == 0);
				CHECK(graph.getEdges().size() == 0);
			}
		}
	}
}