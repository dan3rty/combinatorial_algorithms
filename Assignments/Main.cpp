#include <iostream>
#include <vector>
#include "Assignments.h"

int main()
{
	std::vector<std::vector<int>> skills = { { 0 }, { 1 }, { 2 }, { 3 } };
	std::vector<int> requiredSkills = { 0, 1, 2, 3 };

	std::vector<int> smallestGroup = FindSmallestGroup(skills, requiredSkills);

	std::cout << "The smallest group with all required skills is: ";
	for (int person : smallestGroup)
	{
		std::cout << person << " ";
	}
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
