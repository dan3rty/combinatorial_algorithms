#include "Gamma.h"
#include <algorithm>
#include <vector>

//TODO: �������� ���������� + ������� �������� ������� �� ������

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

// ������� ����, �������� ������� ���������
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

// �������� ������� ������� �����
// ������������ ��� ����� ���������� ���������� �����
// ���� ��� ����������(���� �� ���������), �� null
void Graph::getPlanarLaying()
{
	// ���� ����, ���� ��� ���, �� ���� �� ������������� �������� ���������
	//(��� ������ => ������ => ���������)
	std::vector<int> c = getCycle();
	if (empty(c))
	{
		m_faces = std::vector<std::vector<int>>(0);
		return;
	}
	// ������ ������
	Face extFace = c;
	m_faces.push_back(c);
	m_faces.push_back(extFace);

	// ������� ��� ��������� ������ � ����� ��������������
	std::vector<bool> laidVertexes(m_size);
	std::vector<std::vector<bool>> laidEdges(m_size, std::vector<bool>(m_size, 0));
	for (int i : c)
	{
		laidVertexes[i] = true;
	}
	// ���������� ��������� ����
	layChain(laidEdges, c, true);
	// ������ ��� ���������:
	// ��������� ��������� ���������, ������� ����� ��������� ������,
	// ��������� ����� �� ���������, ������� �����, ���������� ����� ������
	while (true)
	{
		std::vector<Graph> segments = getSegments(laidVertexes, laidEdges);
		// ���� ��� ���������, �� ���� - ��������� ������ ���� => ���������
		if (segments.size() == 0)
		{
			break;
		}
		// ������ ������, � ������� ����� ������� ��������������� �������� � ����������� ������ calcNumOfFacesContainedSegments()
		std::vector<Face> destFaces(segments.size());
		std::vector<int> count = calcNumOfFacesContainedSegments(extFace, segments, laidVertexes, destFaces);

		// ���� ����������� ����� calcNumOfFacesContainedSegments()
		int mi = 0;
		for (int i = 0; i < segments.size(); i++)
		{
			if (count[i] < count[mi])
			{
				mi = i;
			}
		}
		// ���� ���� �� ���� ����, �� ���� �� ���������
		if (count[mi] == 0)
		{
			m_faces = std::vector<Face>(0);
			return;
		}
		else
		{
			// ������� ���������� ��������
			// �������� ���� ����� ����� ����������� ���������
			std::vector<int> chain = segments[mi].getChain(laidVertexes);
			// �������� ������� ���� ��� ���������
			for (int i : chain)
			{
				laidVertexes[i] = true;
			}
			// ���������� ��������������� ����� ����
			layChain(laidEdges, chain, false);

			// ������� �����, ���� ����� ������ ��������� �������
			Face face = destFaces[mi];
			// ����� �����, ����������� ���������� ����� face ��������� ���������
			Face face1;
			Face face2;
			// ���� ������ ���������� ������ ����
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
			// ������� �������� ����(����, ����������� � �������� �����������)
			std::vector<int> reverseChain = chain;
			std::reverse(reverseChain.begin(), reverseChain.end());
			int faceSize = face.size();
			// ���������� ������ ���� � ���� �� ����������� ������,
			// � �������� � ������ � ����������� �� ������� ���������� ������
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
			// ������� ������� �����(��� ��������� �� ��� �����)
			// ��������� ����������� ����� � ��������� ���������� ������
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

// ����� �������� �����, ��������� DFS ��������
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
				// ���� ������
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
			// ������ ����
			std::vector<int> cycle;
			//"�����������" ������� ����� �� ������� ������
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

// ����� ������� ��������� ����� G - G', ������������ ������� �� G,
//  ���� �� ������ ������� ����������� ������� ����������, � ������ G'
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
	// ����� ������������ ���������
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
	// ����� ������� ��������� ����� G - G', ������������ ������� �� G,
	//  ���� �� ������ ������� ����������� ������� ����������, � ������ G'
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

// ����� ���� � ��������� ��������, ��������� DFS ��������
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

// �������� �� ��, ��� ������ ������� ���������� � ������ �����
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

// ������� ����� ������, ��������� ������ �������
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
