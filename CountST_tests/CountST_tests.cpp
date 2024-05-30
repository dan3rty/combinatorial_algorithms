#define CATCH_CONFIG_MAIN
#include "../CountST/Solver.h"
#include "../catch2/catch.hpp"
#include <vector>

TEST_CASE("Test with 4x4")
{
	Matrix adjacencyMatrix = {
		{ 0, 1, 1, 0 },
		{ 1, 0, 1, 0 },
		{ 1, 1, 0, 1 },
		{ 0, 0, 1, 0 }
	};
	Solver solver(adjacencyMatrix);
	solver.CountSpanningTrees();
	int result = solver.GetCountSpanningTrees();

	int expected = 3;

	REQUIRE(result == expected);
}

TEST_CASE("Test with hard 4x4")
{
	Matrix adjacencyMatrix = {
		{ 0, 1, 1, 0 },
		{ 1, 0, 1, 1 },
		{ 1, 1, 0, 1 },
		{ 0, 1, 1, 0 }
	};
	Solver solver(adjacencyMatrix);
	solver.CountSpanningTrees();
	int result = solver.GetCountSpanningTrees();

	int expected = 8;

	REQUIRE(result == expected);
}

TEST_CASE("Test with 5x5")
{
	Matrix adjacencyMatrix = {
		{ 0, 1, 1, 0, 1 },
		{ 1, 0, 1, 1, 0 },
		{ 1, 1, 0, 1, 1 },
		{ 0, 1, 1, 0, 0 },
		{ 1, 0, 1, 0, 0 }
	};
	Solver solver(adjacencyMatrix);
	solver.CountSpanningTrees();
	int result = solver.GetCountSpanningTrees();

	int expected = 21;

	REQUIRE(result == expected);
}

TEST_CASE("Isolated vertex")
{
	Matrix adjacencyMatrix = {
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 1 },
		{ 0, 1, 0, 1 },
		{ 0, 1, 1, 0 }
	};
	Solver solver(adjacencyMatrix);
	solver.CountSpanningTrees();
	int result = solver.GetCountSpanningTrees();

	int expected = 0;

	REQUIRE(result == expected);
}

TEST_CASE("2 components")
{
	Matrix adjacencyMatrix = {
		{ 0, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 1 },
		{ 0, 0, 1, 0 }
	};
	Solver solver(adjacencyMatrix);
	solver.CountSpanningTrees();
	int result = solver.GetCountSpanningTrees();

	int expected = 0;

	REQUIRE(result == expected);
}
