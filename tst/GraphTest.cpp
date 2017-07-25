#include <catch.hpp>
#include <Graph.hpp>

Graph graph;

TEST_CASE("Graph")
{
	Graph graph;

	auto* node1{graph.createNode(50, 100)};
	auto* node2{graph.createNode(10, 20)};
	graph.connect(node1, node2);

	REQUIRE(graph.getWeight(node1, node2) == Approx(89.443f).epsilon(.01f));

	graph.disconnect(node1, node2);
}