#include "Obstacles/Circle.h"
#include <Renderer2D.h>

void Circle::Render(aie::Renderer2D * a_r2d)
{
	a_r2d->setRenderColour(0.f, 1.f, 0.f);
	a_r2d->drawCircle(m_pos.x, m_pos.y, m_radius);
	a_r2d->setRenderColour(0xFFFFFFFF);
}
