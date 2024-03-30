#include <iostream>
#include <vector>

std::vector<int> FindSmallestGroup(std::vector<std::vector<int>> skills, std::vector<int> requiredSkills)
{
	int n = skills.size();
	std::vector<int> smallestGroup;
	int smallestSize = n + 1;

	for (int mask = 0; mask < (1 << n); ++mask)
	{
		std::vector<int> currentGroup;
		std::vector<bool> possessedSkills(requiredSkills.size(), false);

		for (int i = 0; i < n; ++i)
		{
			if (mask & (1 << i))
			{
				currentGroup.push_back(i);
				for (int skill : skills[i])
				{
					possessedSkills[skill] = true;
				}
			}
		}

		bool hasAllRequiredSkills = true;
		for (int skill : requiredSkills)
		{
			if (!possessedSkills[skill])
			{
				hasAllRequiredSkills = false;
				break;
			}
		}

		if (hasAllRequiredSkills && currentGroup.size() < smallestSize)
		{
			smallestSize = currentGroup.size();
			smallestGroup = currentGroup;
		}
	}

	return smallestGroup;
}
