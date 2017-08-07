#pragma once

#include "IBehaviour.hpp"
#include <vector>
#include <glm/vec2.hpp>
#include "Utility.h"

/**
*	@brief Behaviour that handles moving around obstacles.
*/
class CollisionAvoidance : public IBehaviour {
public:
	CollisionAvoidance(float a_fovAngle = FOV_RANGE, float a_losLength = LOS_LENGTH) : m_fovAngle(a_fovAngle), m_losLength(a_losLength) {}
	~CollisionAvoidance();

	virtual void Update(GameObj* a_obj, float a_dt);
	virtual void Render(GameObj* a_obj, aie::Renderer2D* a_r2d);
protected:
	float m_fovAngle;		/*Range of vision to cast out collision detection rays.*/
	float m_losLength;		/*Maximum length of ray cast (Line of Sight)*/

	std::vector<glm::vec2> m_rayVec;	/*DEBUGGING: Store LOS rays to draw them.*/
private:
};