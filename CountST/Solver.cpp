#include "Solver.h"

const double EPS = 1E-9;

int Solver::GetCountSpanningTrees()
{
	return m_countSpanningTrees;
}

Solver::Solver(Matrix& matrix)
{
	m_adjacencyMatrix = matrix;
	Matrix laplacianMatrix(matrix.size(), std::vector<int>(matrix.size(), 0));
	m_laplacianMatrix = laplacianMatrix;
}

void Solver::CountSpanningTrees()
{
	size_t n = m_adjacencyMatrix.size();
	int degree;
	for (size_t i = 0; i < n; i++)
	{
		degree = 0;
		for (size_t j = 0; j < n; j++)
		{
			degree += m_adjacencyMatrix[i][j];
			m_laplacianMatrix[i][j] = -m_adjacencyMatrix[i][j];
		}
		m_laplacianMatrix[i][i] = degree;
	}

	Matrix minor = GetMinor(m_laplacianMatrix, 0, 0);
	m_countSpanningTrees = GetDeterminant(minor);
}

double Solver::GetDeterminant(Matrix& matrix)
{
	size_t size = matrix.size();
	for (int col = 0; col < size; ++col)
	{
		bool found = false;
		for (int row = col; row < size; ++row)
		{
			if (std::abs(matrix[row][col]) > EPS)
			{
				if (row != col)
				{
					matrix[row].swap(matrix[col]);
				}
				found = true;
				break;
			}
		}

		if (!found)
		{
			return 0;
		}

		for (int row = col + 1; row < size; ++row)
		{
			while (true)
			{
				int del = matrix[row][col] / matrix[col][col];;
				for (int j = col; j < size; ++j)
				{
					matrix[row][j] -= del * matrix[col][j];
				}
				if (matrix[row][col] == 0)
				{
					break;
				}
				else
				{
					matrix[row].swap(matrix[col]);
				}
			}
		}
	}

	double res = 1;

	for (int i = 0; i < size; ++i)
	{
		res *= matrix[i][i];
	}
	return abs(res);
}

Matrix Solver::GetMinor(const Matrix& matrix, int row, int column)
{
	size_t minorLength = matrix.size() - 1;
	Matrix minor(minorLength, std::vector<int>(minorLength, 0));

	int dI = 0, dJ = 0;
	for (size_t i = 0; i <= minorLength; i++)
	{
		dJ = 0;
		for (size_t j = 0; j <= minorLength; j++)
		{
			if (i == row)
			{
				dI = 1;
				break;
			}
			else if (j == column)
			{
				dJ = 1;
			}
			else
			{
				minor[i - dI][j - dJ] = matrix[i][j];
			}
		}
	}
	return minor;
}