#include "Gamma.h"
#include <algorithm>
#include <vector>

//TODO: комменты уничтожить + разбить огромную функцию на мелкие

Graph::Graph(Matrix m)
{
	m_matrix = m;
	m_size = m.size();
}

void Graph::addEdge(int k, int m)
{
	m_matrix[k][m] = m_matrix[m][k] = 1;
}

bool Graph::containsEdge(int k, int m)
{
	return (m_matrix[k][m] == 1);
}

std::vector<int> Graph::getCycle()
{
	std::vector<int> cycle;
	std::vector<int> used(m_size);
	bool hasCycle = dfsCycle(cycle, used, -1, 0);
	if (!hasCycle)
	{
		return {};
	}
	else
	{
		std::vector<int> result;
		for (int v : cycle)
		{
			result.push_back(v);
		}
		return result;
	}
}

// Укладка цепи, описание матрицы смежности
void Graph::layChain(std::vector<std::vector<bool>>& result, std::vector<int> chain, bool cyclic)
{
	for (int i = 0; i < chain.size() - 1; i++)
	{
		result[chain[i]][chain[i + 1]] = true;
		result[chain[i + 1]][chain[i]] = true;
	}
	if (cyclic)
	{
		result[chain[0]][chain[chain.size() - 1]] = true;
		result[chain[chain.size() - 1]][chain[0]] = true;
	}
}

// Получить плоскую укладку графа
// Возвращаются все грани уложенного планарного графа
// Если это невозможно(граф не планарный), то null
void Graph::getPlanarLaying()
{
	// Ищем цикл, если его нет, до граф не соответствует условиям алгоритма
	//(Нет циклов => дерево => планарный)
	std::vector<int> c = getCycle();
	if (empty(c))
	{
		m_faces = std::vector<std::vector<int>>(0);
		return;
	}
	// Списки граней
	Face extFace = c;
	m_faces.push_back(c);
	m_faces.push_back(extFace);

	// Массивы уже уложенных вершин и ребер соответственно
	std::vector<bool> laidVertexes(m_size);
	std::vector<std::vector<bool>> laidEdges(m_size, std::vector<bool>(m_size, 0));
	for (int i : c)
	{
		laidVertexes[i] = true;
	}
	// Укладываем найденный цикл
	layChain(laidEdges, c, true);
	// Второй шаг алгоритма:
	// выделение множества сегментов, подсчет числа вмещающих граней,
	// выделение цепей из сегментов, укладка цепей, добавление новых граней
	while (true)
	{
		std::vector<Graph> segments = getSegments(laidVertexes, laidEdges);
		// Если нет сегментов, го граф - найденный постой цикл => планарный
		if (segments.size() == 0)
		{
			break;
		}
		// Массив граней, в которые будут уложены соответствующие сегменты с минимальным числом calcNumOfFacesContainedSegments()
		std::vector<Face> destFaces(segments.size());
		std::vector<int> count = calcNumOfFacesContainedSegments(extFace, segments, laidVertexes, destFaces);

		// Ищем минимальное число calcNumOfFacesContainedSegments()
		int mi = 0;
		for (int i = 0; i < segments.size(); i++)
		{
			if (count[i] < count[mi])
			{
				mi = i;
			}
		}
		// Если хотя бы одно ноль, то граф не планарный
		if (count[mi] == 0)
		{
			m_faces = std::vector<Face>(0);
			return;
		}
		else
		{
			// Укладка выбранного сегмента
			// Выделяем цепь между двумя контактными вершинами
			std::vector<int> chain = segments[mi].getChain(laidVertexes);
			// Помечаем вершины цепи как уложенные
			for (int i : chain)
			{
				laidVertexes[i] = true;
			}
			// Укладываем соответствующие ребра цепи
			layChain(laidEdges, chain, false);

			// Целевая грань, куда будет уложен выбранный сегмент
			Face face = destFaces[mi];
			// Новые грани, порожденные разбиением грани face выбранным сегментом
			Face face1;
			Face face2;
			// Ищем номера контактных вершин цепи
			int contactFirst = 0, contactSecond = 0;
			for (int i = 0; i < face.size(); i++)
			{
				if (face[i] == chain[0])
				{
					contactFirst = i;
				}
				if (face[i] == chain[chain.size() - 1])
				{
					contactSecond = i;
				}
			}
			// Находим обратную цепь(цепь, пробегаемая в обратном направлении)
			std::vector<int> reverseChain = chain;
			std::reverse(reverseChain.begin(), reverseChain.end());
			int faceSize = face.size();
			// Укладываем прямую цепь в одну из порожденных граней,
			// а обратную в другую в зависимости от номеров контактных вершин
			if (contactFirst < contactSecond)
			{
				face1 = chain;
				for (int i = (contactSecond + 1) % faceSize; i != contactFirst; i = (i + 1) % faceSize)
				{
					face1.push_back(face[i]);
				}
				face2 = reverseChain;
				for (int i = (contactFirst + 1) % faceSize; i != contactSecond; i = (i + 1) % faceSize)
				{
					face2.push_back(face[i]);
				}
			}
			else
			{
				face1 = reverseChain;
				for (int i = (contactFirst + 1) % faceSize; i != contactSecond; i = (i + 1) % faceSize)
				{
					face1.push_back(face[i]);
				}
				face2 = chain;
				for (int i = (contactSecond + 1) % faceSize; i != contactFirst; i = (i + 1) % faceSize)
				{
					face2.push_back(face[i]);
				}
			}
			// Удаляем целевую грань(она разбилась на две новые)
			// Добавляем порожденные грани в множество внутренних граней
			m_faces = removeElement(m_faces, face);
			m_faces.push_back(face1);
			m_faces.push_back(face2);
		}
	}
	m_faces.push_back(extFace);
	prepareFacesToOutput(m_faces);
}

std::vector<Face> Graph::getFaces()
{
	return m_faces;
}

void Graph::prepareFacesToOutput(Matrix& graph)
{
	Matrix result;
	for (auto& face : graph)
	{
		for (auto& vertex : face)
		{
			vertex++;
		}
	}
}

std::vector<Face> Graph::removeElement(std::vector<Face> vec, Face element)
{
	std::vector<Face> result;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] != element)
		{
			result.push_back(vec[i]);
		}
	}

	return result;
}

// Поиск простого цикла, используя DFS алгоритм
bool Graph::dfsCycle(std::vector<int>& result, std::vector<int> used, int parent, int v)
{
	used[v] = 1;
	for (int i = 0; i < m_size; i++)
	{
		if (i == parent)
			continue;
		if (m_matrix[v][i] == 0)
			continue;
		if (used[i] == 0)
		{
			result.push_back(v);
			if (dfsCycle(result, used, v, i))
			{
				// Цикл найден
				return true;
			}
			else
			{
				result.pop_back();
			}
		}
		if (used[i] == 1)
		{
			result.push_back(v);
			// Найден цикл
			std::vector<int> cycle;
			//"Выдергиваем" вершины цикла из порядка обхода
			for (int j = 0; j < result.size(); j++)
			{
				if (result[j] == i)
				{
					for (int k = j; k < result.size(); k++)
					{
						cycle.push_back(result[k]);
					}
					result = cycle;
					return true;
				}
			}
			return true;
		}
	}
	used[v] = 2;
	return false;
}

// Поиск связных компонент графа G - G', дополненного ребрами из G,
//  один из концов которых принадлежит связной компоненте, а другой G'
void Graph::dfsSegments(std::vector<int> used, std::vector<bool> laidVertexes, Graph& result, int v)
{
	used[v] = 1;
	for (int i = 0; i < m_size; i++)
	{
		if (m_matrix[v][i] == 1)
		{
			result.addEdge(v, i);
			if (used[i] == 0 && !laidVertexes[i])
			{
				dfsSegments(used, laidVertexes, result, i);
			}
		}
	}
}

std::vector<Graph> Graph::getSegments(std::vector<bool> laidVertexes, std::vector<std::vector<bool>> edges)
{
	std::vector<Graph> segments;
	// Поиск однореберных сегментов
	for (int i = 0; i < m_size; i++)
	{
		for (int j = i + 1; j < m_size; j++)
		{
			if (m_matrix[i][j] == 1 && !edges[i][j] && laidVertexes[i] && laidVertexes[j])
			{
				Matrix m(m_size, std::vector<int>(m_size, 0));
				Graph t(m);
				t.addEdge(i, j);
				segments.push_back(t);
			}
		}
	}
	// Поиск связных компонент графа G - G', дополненного ребрами из G,
	//  один из концов которых принадлежит связной компоненте, а другой G'
	std::vector<int> used(m_size);
	for (int i = 0; i < m_size; i++)
	{
		if (used[i] == 0 && !laidVertexes[i])
		{
			Matrix mat(m_size, Face(m_size, 0));
			Graph res(mat);
			dfsSegments(used, laidVertexes, res, i);
			segments.push_back(res);
		}
	}
	return segments;
}

// Поиск цепи в выбранном сегменте, используя DFS алгоритм
void Graph::dfsChain(std::vector<int> used, std::vector<bool> laidVertexes, std::vector<int>& chain, int v)
{
	used[v] = 1;
	chain.push_back(v);
	for (int i = 0; i < m_size; i++)
	{
		if (m_matrix[v][i] == 1 && used[i] == 0)
		{
			if (!laidVertexes[i])
			{
				dfsChain(used, laidVertexes, chain, i);
			}
			else
			{
				chain.push_back(i);
			}
			return;
		}
	}
}

std::vector<int> Graph::getChain(std::vector<bool> laidVertexes)
{
	std::vector<int> result;

	for (int i = 0; i < m_size; i++)
	{
		if (laidVertexes[i])
		{
			bool inGraph = false;
			for (int j = 0; j < m_size; j++)
			{
				if (containsEdge(i, j))
					inGraph = true;
			}
			if (inGraph)
			{
				std::vector<int> used(m_size);
				dfsChain(used, laidVertexes, result, i);
				break;
			}
		}
	}
	return result;
}

// Проверка на то, что данный сегмент содержится в данной грани
bool Graph::isFaceContainsSegment(const Face face, Graph segment, std::vector<bool> laidVertexes)
{
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			if (segment.containsEdge(i, j))
			{
				if ((laidVertexes[i] && !(std::find(face.begin(), face.end(), i) != face.end())) || (laidVertexes[j] && !(std::find(face.begin(), face.end(), j) != face.end())))
				{
					return false;
				}
			}
		}
	}
	return true;
}

// Считаем число граней, вмещающих данные сегмент
std::vector<int> Graph::calcNumOfFacesContainedSegments(
	Face extFace,
	std::vector<Graph> segments, 
	std::vector<bool> laidVertexes, 
	std::vector<Face>& destFaces)
{
	std::vector<int> count(segments.size());
	for (int i = 0; i < segments.size(); i++)
	{
		for (std::vector<int> face : m_faces)
		{
			if (isFaceContainsSegment(face, segments[i], laidVertexes))
			{
				destFaces[i] = face;
				count[i]++;
			}
		}
		if (isFaceContainsSegment(extFace, segments[i], laidVertexes))
		{
			destFaces[i] = extFace;
			count[i]++;
		}
	}
	return count;
}
