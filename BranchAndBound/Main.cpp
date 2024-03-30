#include "../BranchAndBound/BranchAndBound.h"
#include <iostream>
#include <vector>

int main()
{
	int n = 6;

	std::vector<std::vector<int>> matrix = {
		{ 0, 5, 7, 6, 8, 3 },
		{ 1, 0, 8, 4, 6, 2 },
		{ 3, 9, 0, 6, 5, 3 },
		{ 7, 8, 4, 0, 4, 2 },
		{ 2, 7, 5, 6, 0, 6 },
		{ 5, 2, 6, 4, 5, 0 }
	};

	int min_length = INT_MAX;
	std::vector<std::pair<int, int>> min_path;
	std::vector<std::pair<int, int>> path;
	BranchAndBoundTSP(matrix, path, 0, min_length, min_path);

	std::cout << "Min Path: ";
	for (auto edge : min_path)
	{
		std::cout << ++edge.first << " -> " << ++edge.second << std::endl;
	}
	int length = GetLengthOfPath(matrix, min_path);
	std::cout << "Length: " << length << std::endl;

	return EXIT_SUCCESS;
}
