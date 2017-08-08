#pragma once

#include "Obstacles/IObstacle.h"
#include "Utility.h"

/**
*	@brief Circular shaped obstacle for collision.
*/
class Circle : public IObstacle {
public:
	Circle(glm::vec2& a_pos = glm::vec2(0.f, 0.f), float a_radius = CIRCLE_RAD) : IObstacle(a_pos), m_radius(a_radius) {}
	~Circle() {}

	virtual void Render(aie::Renderer2D* a_r2d);

	float GetRadius() { return m_radius; }

	void SetRadius(float a_radius) { m_radius = a_radius; }
protected:
	float m_radius;
private:
};