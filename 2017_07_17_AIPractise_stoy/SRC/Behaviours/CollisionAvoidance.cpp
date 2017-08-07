#include "Behaviours/CollisionAvoidance.h"
#include <Renderer2D.h>

CollisionAvoidance::~CollisionAvoidance()
{
}

void CollisionAvoidance::Update(GameObj * a_obj, float a_dt)
{
	/*
	1. Cast three rays out in the specified cone of vision
	2. Apply forces in direction of ray that didn't collide into anything, essentially moving around the object
	*/
	
	float currAngle = m_fovAngle / DEFAULT_COLLISION_RAYS;

	for (int r = 0; r < DEFAULT_COLLISION_RAYS; ++r) {
		// Cast out ray clamped by specified length
		glm::vec2 rayVec = glm::vec2(sinf(currAngle), cosf(currAngle)) * m_losLength;
	}
}

void CollisionAvoidance::Render(GameObj * a_obj, aie::Renderer2D * a_r2d)
{
}

