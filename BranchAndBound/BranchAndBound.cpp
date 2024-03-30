#include "../BranchAndBound/BranchAndBound.h"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int GetLengthOfPath(std::vector<std::vector<int>> graph, std::vector<std::pair<int, int>> edges)
{
	int path = 0;
	for (auto edge : edges)
	{
		path += graph[edge.first][edge.second];
	}
	return path;
}

// Функция, которая вычисляет штрафы, вычисляет новую границу, а также находит ребро, которое будем выбирать и возвращает его
std::pair<int, int> ReduceMatrix(std::vector<std::vector<int>>& matrix, int& lowerBound)
{
	int n = matrix.size();
	std::vector<int> rowPenalty;
	std::vector<int> columnPenalty;

	for (int i = 0; i < n; ++i)
	{
		int min_val = INT_MAX;
		for (int j = 0; j < n; ++j)
		{
			if (matrix[i][j] < min_val)
			{
				min_val = matrix[i][j];
			}
		}
		if (min_val != INT_MAX && min_val >= 0)
		{
			rowPenalty.push_back(min_val);
			lowerBound += min_val;
			for (int j = 0; j < n; ++j)
			{
				if (matrix[i][j] != INT_MAX)
				{
					matrix[i][j] -= min_val;
				}
			}
		}
		else
		{
			rowPenalty.push_back(0);
		}
	}

	for (int j = 0; j < n; ++j)
	{
		int min_val = INT_MAX;
		for (int i = 0; i < n; ++i)
		{
			if (matrix[i][j] < min_val)
			{
				min_val = matrix[i][j];
			}
		}
		if (min_val != INT_MAX && min_val >= 0)
		{
			columnPenalty.push_back(min_val);
			lowerBound += min_val;
			for (int i = 0; i < n; ++i)
			{
				if (matrix[i][j] != INT_MAX)
				{
					matrix[i][j] -= min_val;
				}
			}
		}
		else
		{
			columnPenalty.push_back(0);
		}
	}
	
	int maxPenalty = INT_MIN;
	std::pair<int, int> maxPenaltyPoint;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == 0)
			{
				if (rowPenalty[i] + columnPenalty[j] > maxPenalty)
				{
					maxPenaltyPoint = { i, j };
					maxPenalty = rowPenalty[i] + columnPenalty[j];
				}
			}
		}
	}
	return maxPenaltyPoint;
}

void EdgeRemoval(vector<vector<int>>& matrix, std::pair<int, int> indexes)
{
	int n = matrix.size();
	for (int i = 0; i < n; ++i)
	{
		matrix[indexes.first][i] = INT_MAX;
		matrix[i][indexes.second] = INT_MAX;
	}
}

void BranchAndBoundTSP(
	std::vector<std::vector<int>>& matrix,
	std::vector<std::pair<int, int>>& edges,
	int bound,
	int& minBound,
	std::vector<std::pair<int, int>>& minEdges
)
{
	if (edges.size() == matrix.size())
	{
		if (bound < minBound)
		{
			minBound = bound;
			minEdges = edges;
		}
		return;
	}

	int newBound = bound;
	std::vector<std::pair<int, int>> newEdges = edges;
	std::vector<std::pair<int, int>> oldEdges = edges;
	std::vector<std::vector<int>> newMatrix = matrix;

	std::pair<int, int> indexes = ReduceMatrix(newMatrix, newBound);

	if (matrix[indexes.first][indexes.second] == INT_MAX)
	{
		return;
	}

	newEdges.push_back(indexes);
	std::vector<std::vector<int>> matrixWithEdge = newMatrix;

	// Выбрали
	EdgeRemoval(matrixWithEdge, indexes);
	BranchAndBoundTSP(matrixWithEdge, newEdges, newBound + matrix[indexes.first][indexes.second], minBound, minEdges);

	// Не выбрали
	std::vector<std::vector<int>> matrixWithoutEdge = newMatrix;
	matrixWithoutEdge[indexes.first][indexes.second] = INT_MAX;
	BranchAndBoundTSP(matrixWithoutEdge, oldEdges,  newBound + matrix[indexes.first][indexes.second], minBound, minEdges);
}
