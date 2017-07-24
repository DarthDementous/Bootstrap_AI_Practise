#include "Graph/GraphRenderer2D.h"
#include <Renderer2D.h>
#include "Graph/Graph2D.h"
#include "Utility.h"
#include <Font.h>
#include <ResourcePack.h>

void GraphRenderer2D::Draw(aie::Renderer2D* a_r2d)
{
	a_r2d->drawText(ResourcePack::FontMap()["DBG"].get(), "This is a successful test, holy shit.", 100, 100);

	for (auto node : *(m_graph->GetNodes())) {
		glm::vec2 pos = node->GetData();

		// Nodes
		a_r2d->drawCircle(pos.x, pos.y, node->GetRadius(), 1);

		// Edges on the node
		for (auto edge : *(node->GetEdges())) {
			glm::vec2 pos1 = node->GetData();
			glm::vec2 pos2 = edge->m_to->GetData();

			// Edge line
			if (edge->IsBidirected()) {
				a_r2d->setRenderColour(0, 1, 1);
			}
			else {
				a_r2d->setRenderColour(0, 1, 0);
			}
			a_r2d->drawLine(pos1.x, pos1.y, pos2.x, pos2.y);
			
			a_r2d->setRenderColour(0xffffffff);
		}

	}
}
