#include "Behaviours/Wander.h"
#include "Behaviours/Seek.h"
#include <math.h>
#include <MathLib_Utility.h>
#include <glm/gtx/norm.hpp>
#include <Entities/GameObj.h>
#include <Renderer2D.h>

Wander::Wander(float a_radius, float a_dist, float a_jitter) :
	m_radius(a_radius), m_dist(a_dist), m_jitter(a_jitter)
{
	CalculateWanderTarget();
}

void Wander::Update(GameObj* a_obj, Seek* a_beh)
{
	// Entity is within the wander radius, calculate new wander target
	if (glm::length(m_wanderTarget - a_obj->GetPosition()) < m_radius + PLAYER_RADIUS) {
		CalculateWanderTarget(a_obj, a_beh);
	}
}

void Wander::Render(GameObj* a_obj, aie::Renderer2D* a_r2d) {
	// Wander target radius
	a_r2d->drawCircle(m_wanderTarget.x, m_wanderTarget.y, m_radius);

	// Wander vector
	a_r2d->setRenderColour(1.f, 0.f, 0.f);
	a_r2d->drawLine(a_obj->GetPosition().x, a_obj->GetPosition().y, m_wanderTarget.x, m_wanderTarget.y);
	
	a_r2d->setRenderColour(0xFFFFFFFF);
}

void Wander::CalculateWanderTarget(GameObj* a_obj, Seek* a_beh)
{
	//1. Find random point along the edge of current wander circle by calculating random angle 0-6 (about 360 degrees in radians)
	m_wanderTarget = glm::vec2(cosf(rand() % (int)_2PI) * m_radius, cosf(rand() % (int)_2PI) * m_radius);

	//2. Apply jitter
	glm::vec2 jitterVec = glm::vec2(rand() % (int)m_jitter, rand() % (int)m_jitter);
	m_wanderTarget += jitterVec;

	//3. Normalize and scale back inside radius after jitter
	m_wanderTarget = glm::normalize(m_wanderTarget) * m_radius;

	//4. Apply to current object's velocity scaling by distance
	m_wanderTarget += a_obj->GetVelocity() * m_dist;

	//5. Set entity to seek calculated wander target
	a_obj->SetBehaviour(a_beh);
}
