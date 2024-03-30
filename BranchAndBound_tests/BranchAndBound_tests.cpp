#include <vector>
#define CATCH_CONFIG_MAIN
#include "../BranchAndBound/BranchAndBound.h"
#include "../catch2/catch.hpp"

TEST_CASE("Test for 3x3 matrix")
{
	std::vector<std::vector<int>> graph = {
		{ INT_MAX, 2, 1 },
		{ 5, INT_MAX, 9 },
		{ 10, 7, INT_MAX }
	};
	int minBound = INT_MAX;
	std::vector<std::pair<int, int>> minEdges;
	std::vector<std::pair<int, int>> edges;
	BranchAndBoundTSP(graph, edges, 0, minBound, minEdges);
	CHECK(minBound != INT_MAX);
	int length = GetLengthOfPath(graph, minEdges);
	std::vector<std::pair<int, int>> expectedPath = {
		{ 2, 1 },
		{ 0, 2 },
		{ 1, 0 }
	};
	int expectedLength = 13;
	CHECK(minEdges == expectedPath);
	CHECK(length == expectedLength);
}

TEST_CASE("Test for 4x4 matrix")
{
	std::vector<std::vector<int>> graph = {
		{ INT_MAX, 5, 11, 9 },
		{ 10, INT_MAX, 8, 7 },
		{ 7, 14, INT_MAX, 8 },
		{ 12, 6, 15, INT_MAX }
	};
	int minBound = INT_MAX;
	std::vector<std::pair<int, int>> minEdges;
	std::vector<std::pair<int, int>> edges;
	BranchAndBoundTSP(graph, edges, 0, minBound, minEdges);
	CHECK(minBound != INT_MAX);
	int length = GetLengthOfPath(graph, minEdges);
	std::vector<std::pair<int, int>> expectedEdges = {
		{ 1, 2 },
		{ 0, 3 },
		{ 2, 0 },
		{ 3, 1 }
	};
	int expectedLength = 30;
	CHECK(minEdges == expectedEdges);
	CHECK(length == expectedLength);
}

TEST_CASE("Test for 5x5 matrix oriented")
{
	std::vector<std::vector<int>> graph = {
		{ INT_MAX, 1, 0, 1, 1 },
		{ 1, INT_MAX, 1, 1, 0 },
		{ 1, 1, INT_MAX, 0, 1 },
		{ 1, 0, 1, INT_MAX, 1 },
		{ 0, 1, 1, 1, INT_MAX },
	};
	int min_length = INT_MAX;
	std::vector<std::pair<int, int>> min_edges;
	std::vector<std::pair<int, int>> edges;
	BranchAndBoundTSP(graph, edges, 0, min_length, min_edges);
	CHECK(min_length != INT_MAX);
	int length = GetLengthOfPath(graph, min_edges);
	std::vector<std::pair<int, int>> expected_path = {
		{ 0, 2 },
		{ 1, 4 },
		{ 2, 3 },
		{ 3, 1 },
		{ 4, 0 }
	};
	int expected_length = 0;
	CHECK(min_edges == expected_path);
	CHECK(length == expected_length);
}

TEST_CASE("Test for 6x6 matrix")
{
	std::vector<std::vector<int>> graph = {
		{ INT_MAX, 5, 7, 6, 8, 3 },
		{ 1, INT_MAX, 8, 4, 6, 2 },
		{ 3, 9, INT_MAX, 6, 5, 3 },
		{ 7, 8, 4, INT_MAX, 4, 2 },
		{ 2, 7, 5, 6, INT_MAX, 6 },
		{ 5, 2, 6, 4, 5, INT_MAX }
	};
	int minBound = INT_MAX;
	std::vector<std::pair<int, int>> minEdges;
	std::vector<std::pair<int, int>> edges;
	BranchAndBoundTSP(graph, edges, 0, minBound, minEdges);
	CHECK(minBound != INT_MAX);
	int length = GetLengthOfPath(graph, minEdges);
	std::vector<std::pair<int, int>> expectedPath = {
		{ 2, 4 },
		{ 0, 5 },
		{ 1, 3 },
		{ 3, 2 },
		{ 4, 0 },
		{ 5, 1 }
	};
	int expectedLength = 20;
	CHECK(minEdges == expectedPath);
	CHECK(length == expectedLength);
}
