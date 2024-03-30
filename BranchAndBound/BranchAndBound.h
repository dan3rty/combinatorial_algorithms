#pragma once
#include <vector>

using namespace std;

int Min(const vector<int>& lst, int myindex);

void Delete(vector<vector<int>>& matrix, int index1, int index2);

void BranchAndBoundTSP(
	std::vector<std::vector<int>>& matrix,
	std::vector<std::pair<int, int>>& edges,
	int bound,
	int& min_bound,
	std::vector<std::pair<int, int>>& min_edges
);

int GetLengthOfPath(std::vector<std::vector<int>> graph, std::vector<std::pair<int, int>> edges);