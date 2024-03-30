#include "../Assignments/Assignments.h"
#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include <vector>

TEST_CASE("Count of peoples equals to count of skills")
{
	std::vector<std::vector<int>> inputSkills = { { 0 }, { 1 }, { 2 }, { 3 } };
	std::vector<int> inputRequiredSkills = { 0, 1, 2, 3 };
	std::vector<int> result = FindSmallestGroup(inputSkills, inputRequiredSkills);
	std::vector<int> expected = { 0, 1, 2, 3 };
	REQUIRE(result == expected);
}

TEST_CASE("Count of skills is greater then count of people")
{
	std::vector<std::vector<int>> inputSkills = { { 0 }, { 1 }, { 2 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { 2, 3 } };
	std::vector<int> inputRequiredSkills = { 0, 1, 2, 3 };
	std::vector<int> result = FindSmallestGroup(inputSkills, inputRequiredSkills);
	std::vector<int> expected = { 3, 6 };
	REQUIRE(result == expected);
}

TEST_CASE("Group doesnt exists")
{
	std::vector<std::vector<int>> inputSkills = { { 0 }, { 1 }, { 2 } };
	std::vector<int> inputRequiredSkills = { 0, 1, 2, 3 };
	std::vector<int> result = FindSmallestGroup(inputSkills, inputRequiredSkills);
	std::vector<int> expected = { };
	REQUIRE(result == expected);
}

TEST_CASE("1 very smart human")
{
	std::vector<std::vector<int>> inputSkills = { { 0 }, { 1 }, { 2 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { 2, 3 }, { 0, 1, 2, 3 }};
	std::vector<int> inputRequiredSkills = { 0, 1, 2, 3 };
	std::vector<int> result = FindSmallestGroup(inputSkills, inputRequiredSkills);
	std::vector<int> expected = { 7 };
	REQUIRE(result == expected);
}

TEST_CASE("test")
{
	std::vector<std::vector<int>> inputSkills = { { 0, 1, 2, 3 }, { 4 }, { 5 }, { 0, 1, 4 }, { 2, 3, 5 } };
	std::vector<int> inputRequiredSkills = { 0, 1, 2, 3, 4, 5 };
	std::vector<int> result = FindSmallestGroup(inputSkills, inputRequiredSkills);
	std::vector<int> expected = { 3, 4 };
	REQUIRE(result == expected);
}