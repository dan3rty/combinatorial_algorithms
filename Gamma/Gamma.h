#pragma once
#include <algorithm>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
using Face = std::vector<int>;

class Graph
{
public:
	Graph(Matrix m);

	void addEdge(int k, int m);

	bool containsEdge(int k, int m);

	std::vector<int> getCycle();

	static void layChain(std::vector<std::vector<bool>>& result, std::vector<int> chain, bool cyclic);

	void getPlanarLaying();

	std::vector<Face> getFaces();

private:
	Matrix m_matrix;
	int m_size = 0;
	std::vector<Face> m_faces;

	void prepareFacesToOutput(Matrix& graph);

	std::vector<std::vector<int>> removeElement(std::vector<Face> vec, Face element);

	bool dfsCycle(std::vector<int>& result, std::vector<int> used, int parent, int v);

	void dfsSegments(std::vector<int> used, std::vector<bool> laidVertexes, Graph& result, int v);

	std::vector<Graph> getSegments(std::vector<bool> laidVertexes, std::vector<std::vector<bool>> edges);

	void dfsChain(std::vector<int> used, std::vector<bool> laidVertexes, std::vector<int>& chain, int v);

	std::vector<int> getChain(std::vector<bool> laidVertexes);

	bool isFaceContainsSegment(const Face face, Graph segment, std::vector<bool> laidVertexes);

	std::vector<int> calcNumOfFacesContainedSegments(
		Face extFace,
		std::vector<Graph> segments,
		std::vector<bool> laidVertexes,
		std::vector<Face>& destFaces);
};
