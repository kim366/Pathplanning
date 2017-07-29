#include <catch.hpp>

SCENARIO("Dijkstra's Algorithm finds the shortest path and expands the correct amount of nodes")
{
	GIVEN("A Graph with some Nodes and Edges and Pointers to Start & End Nodes")
	// Image & Geogebra File: http://bit.ly/2v6fuJT
	// Start Node in Green End Node in Red
	// Shortest Path in Orange (400.67)

	enum Nodes
	{
		A, B, C, D, E, F, G
	};

	Graph graph
	{
		{168, 123},
		{172, 70},
		{106, 255},
		{402, 40},
		{363, 271},
		{483, 188},
		{306, 164}
	},
	{
		{C, E},
		{C, A},
		{E, A},
		{E, G},
		{E, F},
		{A, G},
		{A, B},
		{G, B},
		{G, D},
		{F, D},
		{B, D}
	};

	Node* start_node{graph.getNode(5)};
	Node* end_node{graph.getNode(4)};

	WHEN("Dijkstra's Algorithm finds the shortest Path")
	{
		auto result{DijkstrasPathplanner(start_node, end_node)};

		THEN("It finds the shortest Path")
		{
			REQUIRE(result.first == {graph.getNode(B), graph.getNode(D), graph.getNode(F)});
		}

		THEN("It expands the correct Number of Nodes")
		{
			REQUIRE(result.second == 7); // expands all nodes
		}
	}
}