#pragma once
#include <vector>
#include <iostream>

using Matrix = std::vector<std::vector<int>>;

class Solver
{
public:
	Solver(Matrix& matrix);
	void CountSpanningTrees();
	int GetCountSpanningTrees();
private:
	double GetDeterminant(Matrix& matrix);
	Matrix GetMinor(const Matrix& matrix, int row, int column);

	Matrix m_adjacencyMatrix;
	Matrix m_laplacianMatrix;
	int m_countSpanningTrees = 0;
};
