#include "Graph/GraphRenderer2D.h"
#include <Renderer2D.h>
#include "Graph/Graph2D.h"
#include "Utility.h"
#include <Font.h>
#include <ResourcePack.h>
#include <Input.h>

void GraphRenderer2D::Draw(aie::Renderer2D* a_r2d)
{
	a_r2d->drawText(ResourcePack::FontMap()["DBG"].get(), "This is a successful test, holy shit.", 100, 100);

#pragma region Graph
	a_r2d->setRenderColour(0x6b6c6dFF);
	for (auto node : *(m_graph->GetNodes())) {
		glm::vec2 pos = node->GetData();

		// Nodes
		a_r2d->drawCircle(pos.x, pos.y, node->GetRadius(), 1.f);

		// Edges on the node
		for (auto edge : *(node->GetEdges())) {
			glm::vec2 destPos = edge->m_to->GetData();

			// Edge line
			if (edge->IsBidirected()) {
				//a_r2d->setRenderColour(0, 1, 1);
			}
			else {
				a_r2d->setRenderColour(0, 1, 0);
			}
			a_r2d->drawLine(pos.x, pos.y, destPos.x, destPos.y, 1.f, 2.f);
		}

	}
	a_r2d->setRenderColour(0xffffffff);
#pragma endregion

	aie::Input* input = aie::Input::getInstance();
	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);

	// Draw lines from nodes (that are in range) to the cursor
	for (auto nearNode : m_graph->GetNearbyNodes(glm::vec2(mouseX, mouseY), SEARCH_RADIUS / 2)) {
		a_r2d->drawLine(nearNode->GetData().x, nearNode->GetData().y, (float)mouseX, (float)mouseY);

		// Draw search radius
		#ifdef _DEBUG
		a_r2d->setRenderColour(1.f, 0.f, 0.f, 0.1f);
		a_r2d->drawCircle((float)mouseX, (float)mouseY, SEARCH_RADIUS / 2);
		a_r2d->setRenderColour(0xFFFFFFFF);
		#endif
	}
}
