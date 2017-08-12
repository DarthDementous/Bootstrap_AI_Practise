#pragma once

#include "IObstacle.h"
#include "Utility.h"

/**
*	@brief Rectangle shaped obstacle.
*/
class Rect : public IObstacle {
public:
	Rect(glm::vec2 a_pos = glm::vec2(0.f, 0.f), glm::vec2 a_extents = RECT_EXTENTS);
	virtual ~Rect() {}

	virtual void Render(aie::Renderer2D* a_r2d);

	// Calculate max and min from position and extents
	glm::vec2 GetMax();
	glm::vec2 GetMin();
protected:
	glm::vec2 m_extents;		/*Width and height respectively.*/
private:
};