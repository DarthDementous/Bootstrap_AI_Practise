#pragma once

#pragma region Forward Declarations
class Graph2D;

namespace aie {
	class Renderer2D;
}
#pragma endregion

/**
*	@brief Class for displaying a 2D graph by its vertices and edges.
*/
class GraphRenderer2D {
public:
	GraphRenderer2D(Graph2D* a_graph) : m_graph(a_graph) {}

	const Graph2D* GetGraph() { return m_graph; }

	void SetGraph(Graph2D* a_graph) { m_graph = a_graph; }

	void Draw(aie::Renderer2D* a_r2d);
protected:
private:
	Graph2D* m_graph;
};