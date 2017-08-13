#include "Obstacles/Tri.h"
#include <Renderer2D.h>
#include "Utility.h"

Tri::Tri(glm::vec2 a_v1, glm::vec2 a_v2, glm::vec2 a_v3)
{
	// Add vertices
	m_verts[0] = a_v1;
	m_verts[1] = a_v2;
	m_verts[2] = a_v3;

	// Calculate center of gravity (position of triangle)
	m_pos = CalculateCenter();

}

Tri::Tri(glm::vec2 a_verts[3])
{
	// Copy over vertices
	for (size_t i = 0; i < 3; ++i) {
		m_verts[i] = a_verts[i];
	}

	// Calculate center of gravity (position of triangle)
	m_pos = CalculateCenter();
}

Tri::~Tri()
{

}

void Tri::Render(aie::Renderer2D * a_r2d)
{
	a_r2d->setRenderColour(0.f, 1.f, 0.f);

	// AB
	a_r2d->drawLine(m_verts[0].x, m_verts[0].y, m_verts[1].x, m_verts[1].y);
	// BC
	a_r2d->drawLine(m_verts[1].x, m_verts[1].y, m_verts[2].x, m_verts[2].y);
	// CA
	a_r2d->drawLine(m_verts[2].x, m_verts[2].y, m_verts[0].x, m_verts[0].y);

	a_r2d->setRenderColour(0xFFFFFFFF);
}

glm::vec2 Tri::CalculateCenter()
{
	// Find the average of the three points
	glm::vec2 sum;

	for (size_t i = 0; i < 3; ++i) {
		sum += m_verts[i];
	}

	return sum / 3.f;
}
