#include <iostream>
#include <vector>

class Faces
{
public:
	Faces(std::vector<std::vector<int>> interior)
	{
		if (!empty(interior))
		{
			m_interior = interior;
			m_size = interior.size();
		}
		else
		{
			m_size = 0;
		}
	}

	std::vector<std::vector<int>> getInterior()
	{
		return m_interior;
	}

	void print()
	{
		std::cout << "Faces size = " << m_size << std::endl
				  << "Faces: " << std::endl;
		for (auto vec : m_interior)
		{
			for (auto element : vec)
			{
				std::cout << element + 1 << " ";
			}
			std::cout << std::endl;
		}
	}

private:
	std::vector<std::vector<int>> m_interior;
	int m_size;
};
