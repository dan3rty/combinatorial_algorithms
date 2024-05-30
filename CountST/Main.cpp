#include "Solver.h"
#include <iostream>
#include <vector>

int main()
{
	std::vector<std::vector<int>> adjacencyMatrix = {
		{ 0, 1, 1, 0 },
		{ 1, 0, 1, 0 },
		{ 1, 1, 0, 1 },
		{ 0, 0, 1, 0 }
	};
	Solver solver(adjacencyMatrix);
	solver.CountSpanningTrees();
	int result = solver.GetCountSpanningTrees();
	std::cout << "Number of spanning trees in the graph: " << result << std::endl;

	return 0;
}