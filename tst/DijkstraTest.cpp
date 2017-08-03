#include <catch.hpp>
#include <Graph.hpp>
#include <DijkstrasPathplanner.hpp>

enum
{
	A, B, C, D, E, F, G
};

SCENARIO("Dijkstra's Algorithm finds the shortest path and expands the correct amount of nodes")
{
	GIVEN("A Graph with some Nodes and Edges and Pointers to Start & End Nodes \
		and Dijkstra's Pathplanner Object")
	{
		// Image & Geogebra File: http://bit.ly/2v6fuJT
		// Start Node in Green End Node in Red
		// Shortest Path in Orange (400.67)

		Graph graph
		{
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
			}
		};

		const Node* start_node{graph.getNode(B)};
		const Node* end_node{graph.getNode(F)};

		DijkstrasPathplanner find_shortest_path;

		WHEN("Dijkstra's Algorithm attempts to find the shortest Path")
		{
			auto result{find_shortest_path(start_node, end_node)};

			THEN("It finds the shortest Path")
			{
				REQUIRE(result);
				INFO('A' << graph.getNode(A));
				INFO('B' << graph.getNode(B));
				INFO('C' << graph.getNode(C));
				INFO('D' << graph.getNode(D));
				INFO('E' << graph.getNode(E));
				INFO('F' << graph.getNode(F));
				INFO('G' << graph.getNode(G));
				std::vector<const Node*>
					target_path{graph.getNode(B), graph.getNode(D), graph.getNode(F)};
				CHECK(result->first == target_path);
			}

			THEN("It examines the correct Number of Nodes")
			{
				CHECK(result->second == 7); // examines all nodes
			}
		}
	}
}