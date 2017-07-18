#include "Graph/GraphRenderer2D.h"
#include <Renderer2D.h>
#include "Graph/Graph2D.h"
#include "Utility.h"

void GraphRenderer2D::Draw(aie::Renderer2D* a_r2d)
{
	for (auto node : *(m_graph->GetNodes())) {
		glm::vec2 pos = node->GetData();

		// Nodes
		a_r2d->drawCircle(pos.x, pos.y, NODE_RADIUS, 1);

		// Edges on the node
		for (auto edge : *(node->GetEdges())) {
			glm::vec2 pos1 = node->GetData();
			glm::vec2 pos2 = edge->m_to->GetData();

			a_r2d->setRenderColour(0xff0000ff);
			a_r2d->drawLine(pos1.x, pos1.y, pos2.x, pos2.y);
			a_r2d->setRenderColour(0xffffffff);
		}

	}
}
