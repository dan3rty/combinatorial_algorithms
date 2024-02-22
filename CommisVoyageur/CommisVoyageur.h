#pragma once
#include <algorithm>
#include <boost/timer.hpp>
#include <climits>
#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<size_t>>;

class CommisVoyageur
{
public:
	explicit CommisVoyageur(const Matrix& roads)
		: m_roads(std::move(roads)){};
	std::vector<size_t> CountBestPermutation();
	void OutputPermutation(const std::vector<size_t>& permutation);

private:
	Matrix m_roads;
};