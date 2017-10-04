#include <iterator>
#include <catch.hpp>
#include <Graph.hpp>

SCENARIO("Graphs work properly")
{
	GIVEN("An empty Graph")
	{
		Graph graph;

		WHEN("Two Nodes are connected")
		{	
			graph.createNode({50, 100});
			graph.createNode({10, 20});

			auto* node2{graph.getNode(1)}; 
			auto* node1{graph.getNode(1)}; 
			

			graph.connect({0, 1});
		}
	}
}