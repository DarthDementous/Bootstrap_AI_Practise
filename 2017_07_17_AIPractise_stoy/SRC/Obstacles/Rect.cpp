#include "Obstacles/Rect.h"
#include <Renderer2D.h>

Rect::Rect(glm::vec2 a_pos, glm::vec2 a_extents) : m_extents(a_extents) 
{
	m_pos = a_pos;
}

void Rect::Render(aie::Renderer2D * a_r2d)
{
	a_r2d->setRenderColour(1.f, 1.f, 0.f);
	a_r2d->drawBox(m_pos.x, m_pos.y, m_extents.x, m_extents.y);

	// Max and min
#ifdef _DEBUG
	a_r2d->setRenderColour(1.f, 0.f, 0.f);
	a_r2d->drawCircle(GetMax().x, GetMax().y, 4.f);
	a_r2d->drawCircle(GetMin().x, GetMin().y, 4.f);
#endif

	a_r2d->setRenderColour(0xFFFFFFFF);
}

glm::vec2 Rect::GetMax()
{
	glm::vec2 halfExtents = m_extents / 2.f;

	// Top left hand corner
	return glm::vec2(m_pos.x - halfExtents.x, m_pos.y + halfExtents.y);
}

glm::vec2 Rect::GetMin()
{
	glm::vec2 halfExtents = m_extents / 2.f;

	// Bottom right hand corner
	return glm::vec2(m_pos.x + halfExtents.x, m_pos.y - halfExtents.y);
}
