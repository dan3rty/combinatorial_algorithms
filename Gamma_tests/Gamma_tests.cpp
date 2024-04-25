#define CATCH_CONFIG_MAIN
#include "../Gamma/Gamma.h"
#include "../catch2/catch.hpp"
#include <vector>

TEST_CASE("Test with K4")
{
	Matrix matrix = {
		{ 0, 1, 1, 1 },
		{ 1, 0, 1, 1 },
		{ 1, 1, 0, 1 },
		{ 1, 1, 1, 0 }
	};

	Graph graph(matrix);
	graph.getPlanarLaying();
	std::vector<Face> planar = graph.getFaces();

	std::vector<Face> expectedPlanar = {
		{ 2, 4, 1 },
		{ 4, 3, 1 },
		{ 3, 4, 2 },
		{ 1, 2, 3 }
	};

	REQUIRE(planar == expectedPlanar);
}

TEST_CASE("Test with K5")
{
	Matrix matrix = {
		{ 0, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 1 },
		{ 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1 },
		{ 1, 1, 1, 1, 0 }
	};

	Graph graph(matrix);
	graph.getPlanarLaying();
	std::vector<Face> planar = graph.getFaces();

	int expectedPlanarSize = 0;

	REQUIRE(planar.size() == expectedPlanarSize);
}

TEST_CASE("Test with cube")
{
	Matrix matrix = {
		{ 0, 1, 0, 1, 1, 0, 0, 0 },
		{ 1, 0, 1, 0, 0, 1, 0, 0 },
		{ 0, 1, 0, 1, 0, 0, 1, 0 },
		{ 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 0, 1 },
		{ 0, 1, 0, 0, 1, 0, 1, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 1, 0, 1, 0 }
	};

	Graph graph(matrix);
	graph.getPlanarLaying();
	std::vector<Face> planar = graph.getFaces();

	std::vector<Face> expectedPlanar = {
		{ 2, 6, 5, 1 },
		{ 3, 7, 6, 2 },
		{ 5, 8, 4, 1 },
		{ 8, 7, 3, 4 },
		{ 7, 8, 5, 6 },
		{ 1, 2, 3, 4 }
	};

	REQUIRE(planar == expectedPlanar);
}

TEST_CASE("Test with average graph")
{
	Matrix matrix = {
		{ 0, 1, 0, 0, 1, 0, 1, 1 },
		{ 1, 0, 1, 1, 0, 0, 1, 1 },
		{ 0, 1, 0, 1, 0, 0, 0, 1 },
		{ 0, 1, 1, 0, 0, 1, 1, 0 },
		{ 1, 0, 0, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 1, 1, 0, 1, 0 },
		{ 1, 1, 0, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 0, 0, 0, 0, 0 }
	};

	Graph graph(matrix);
	graph.getPlanarLaying();
	std::vector<Face> planar = graph.getFaces();

	std::vector<Face> expectedPlanar = {
		{ 2, 8, 1 },
		{ 8, 3, 4, 6, 5, 1 },
		{ 3, 8, 2 },
		{ 1, 7, 2 },
		{ 7, 4, 2 },
		{ 5, 7, 1 },
		{ 7, 6, 4 },
		{ 6, 7, 5 },
		{ 2, 3, 4 }
	};

	REQUIRE(planar == expectedPlanar);
}

TEST_CASE("Test with Halin`s graph")
{
	Matrix matrix = {
		{ 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 }
	};

	Graph graph(matrix);
	graph.getPlanarLaying();
	std::vector<Face> planar = graph.getFaces();

	std::vector<Face> expectedPlanar = {
		{ 11, 12, 15, 21, 5, 6, 7 },
		{ 6, 4, 2, 3, 7 },
		{ 4, 6, 5 },
		{ 9, 13, 11, 10 },
		{ 8, 10, 11, 7, 3, 1 },
		{ 10, 8, 9 },
		{ 13, 14, 12, 11 },
		{ 14, 16, 17, 15, 12 },
		{ 16, 18, 17 },
		{ 18, 19, 17 },
		{ 19, 20, 17 },
		{ 20, 21, 15, 17 },
		{ 21, 20, 19, 18, 16, 14, 13, 9, 8, 1, 2, 4, 5 },
		{ 1, 2, 3 }
	};

	REQUIRE(planar == expectedPlanar);
}
