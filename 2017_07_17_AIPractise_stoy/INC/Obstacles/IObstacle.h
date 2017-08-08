#pragma once

#include <glm/vec2.hpp>

namespace aie {
	class Renderer2D;
}
/**
*	@brief Base class for objects used for the collision avoidance behaviour.
*/
class IObstacle {
public:
	IObstacle(glm::vec2& a_pos = glm::vec2(0.f, 0.f)) : m_pos(a_pos) {}
	~IObstacle() {}

	virtual void Render(aie::Renderer2D* a_r2d);

	const glm::vec2& GetPos() { return m_pos; }

	void SetPos(glm::vec2& a_pos) { m_pos = a_pos; }
protected:
	glm::vec2 m_pos;			/*Position of obstacle (center of object).*/
private:
};