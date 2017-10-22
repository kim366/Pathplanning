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
		and Pathplanner Objects and a Target Shortest Path")
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

		const Node* start{graph.getNode(B)};
		const Node* goal{graph.getNode(F)};

		DijkstrasPathplanner dijkstra_find_shortest_path{graph};
		AStarPathplanner<Euclidean> astar_find_shortest_path{graph};

		INFO('A' << graph.getNode(A));
		INFO('B' << graph.getNode(B));
		INFO('C' << graph.getNode(C));
		INFO('D' << graph.getNode(D));
		INFO('E' << graph.getNode(E));
		INFO('F' << graph.getNode(F));
		INFO('G' << graph.getNode(G));

		std::vector<const Node*>
			target_path{graph.getNode(B), graph.getNode(D), graph.getNode(F)};

		WHEN("Dijkstra's Algorithm attempts to find the shortest Path")
		{
			auto result{dijkstra_find_shortest_path(start, goal)};

			THEN("It finds the shortest Path")
			{
				CHECK(result.first == target_path);
			}

			THEN("It examines the correct Number of Nodes")
			{
				CHECK(result.second.size() == 7); // examines all nodes
			}
		}

		WHEN("A* attempts to find the shortest Path")
		{
			auto result{astar_find_shortest_path(start, goal)};

			THEN("It finds the shortest Path")
			{
				CHECK(result.first == target_path);
			}

			THEN("It examines fewer Nodes than Dijkstra's Pathplanner")
			{
				CHECK(result.second.size() < 7); // examines all nodes
			}
		}
	}

	GIVEN("A nonempty Graph with disconnected Nodes \
		and Pointers to Start & End Nodes and Pathplanner Objects")
	{
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
				{A, G},
				{A, B},
				{G, B},
				{G, D},
				{B, D}
			}
		};

		const Node* start{graph.getNode(B)};
		const Node* goal{graph.getNode(F)};

		DijkstrasPathplanner dijkstra_find_shortest_path{graph};
		AStarPathplanner<Euclidean> astar_find_shortest_path{graph};

		INFO('A' << graph.getNode(A));
		INFO('B' << graph.getNode(B));
		INFO('C' << graph.getNode(C));
		INFO('D' << graph.getNode(D));
		INFO('E' << graph.getNode(E));
		INFO('F' << graph.getNode(F));
		INFO('G' << graph.getNode(G));

		WHEN("Dijkstra's Algorithm attempts to find the shortest Path")
		{
			auto result{dijkstra_find_shortest_path(start, goal)};

			THEN("It terminates unsuccessfully")
			{
				REQUIRE(result.first.empty());
			}
		}

		WHEN("A* attempts to find the shortest Path")
		{
			auto result{astar_find_shortest_path(start, goal)};

			THEN("It terminates unsuccessfully")
			{
				REQUIRE(result.first.empty());
			}
		}
	}
}

