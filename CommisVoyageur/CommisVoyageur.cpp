#include "CommisVoyageur.h"

std::vector<size_t> CommisVoyageur::CountBestPermutation()
{
	std::vector<size_t> permutations;
	for (size_t i = 1; i <= m_roads.size(); i++)
	{
		permutations.push_back(i);
	}
	std::vector<size_t> bestPermutation;
	size_t min = INT_MAX;
	do
	{
		size_t sum = 0;
		for (size_t i = 0; i < permutations.size(); i++)
		{
			sum += m_roads[permutations[i] - 1][permutations[(i + 1) % (permutations.size())] - 1];
		}
		if (sum < min)
		{
			min = sum;
			bestPermutation = permutations;
		}
	} while (std::next_permutation(permutations.begin(), permutations.end()));
	return bestPermutation;
}

void CommisVoyageur::OutputPermutation(const std::vector<size_t>& permutation)
{
	for (size_t i = 0; i < permutation.size(); i++)
	{
		std::cout << permutation[i] << std::endl;
	}
}