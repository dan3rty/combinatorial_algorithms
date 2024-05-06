#include "Gamma.h"
#include <iostream>
#include <vector>

void print(std::vector<std::vector<int>> faces)
{
	std::cout << "Faces size = " << faces.size() << std::endl
			  << "Faces: " << std::endl;
	for (auto vec : faces)
	{
		for (auto element : vec)
		{
			std::cout << element + 1 << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	//std::vector<std::vector<int>> graph = {
	//	{ 0, 1, 1, 1 },
	//	{ 1, 0, 1, 1 },
	//	{ 1, 1, 0, 1 },
	//	{ 1, 1, 1, 0 }
	//};
	/*std::vector<std::vector<int>> graph = {
		{ 0, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 1 },
		{ 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1 },
		{ 1, 1, 1, 1, 0 }
	};*/

	 std::vector<std::vector<int>> graph = {
		{ 0, 1, 0, 1, 1, 0, 0, 0 },
		{ 1, 0, 1, 0, 0, 1, 0, 0 },
		{ 0, 1, 0, 1, 0, 0, 1, 0 },
		{ 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 0, 1 },
		{ 0, 1, 0, 0, 1, 0, 1, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 1, 0, 1, 0 }
	 };
	//  написать вывод исходного графа
	Graph gr(graph);
	gr.getPlanarLaying();
	std::vector<std::vector<int>> planar = gr.getFaces();
	if (planar.size() != 0)
	{
		std::cout << "Graph is planar!!! Faces of planar graph:" << std::endl;
		print(planar);
	}
	else
	{
		std::cout << "Graph is not planar :(" << std::endl;
	}

	return EXIT_SUCCESS;
}
