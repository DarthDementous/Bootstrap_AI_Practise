#include "Behaviours/Wander.h"
#include "Behaviours/Seek.h"
#include <math.h>
#include <MathLib_Utility.h>
#include <glm/gtx/norm.hpp>
#include <Entities/IAgent.h>
#include <Renderer2D.h>
#include <math.h>
#include <random>
#include <ctime>


void Wander::Startup()
{
	// Calculate first wander vector
	CalculateWander();
}

void Wander::Update(float a_dt) {
	// Move in current wander direction
	m_obj->ApplyForce(m_wanderDir);

	// Calculate new wander vector every interval
	static float timer = WANDER_TIMER;
	
	timer -= a_dt;

	if (timer < 0) {
		CalculateWander();
		timer = WANDER_TIMER;
	}
}

void Wander::Draw(aie::Renderer2D* a_r2d) {
#ifdef _DEBUG
	// Initial wander target radius
	a_r2d->setRenderColour(0.f, 1.f, 1.f, 0.5f);
	a_r2d->drawCircle(m_obj->GetPosition().x, m_obj->GetPosition().y, m_radius);

	// Projected wander target radius
	a_r2d->setRenderColour(1.f, 1.f, 1.f, 0.5f);
	glm::vec2 projectedPos = m_obj->GetPosition() + m_projectedVec;
	a_r2d->drawCircle(projectedPos.x, projectedPos.y, m_radius);

	// Initial random position on circumference
	a_r2d->setRenderColour(1.f, 0.f, 0.f, 1.f);
	glm::vec2 circumPos = m_obj->GetPosition() + m_randDir;
	a_r2d->drawCircle(circumPos.x, circumPos.y, 4.f);

	// Jitter vector
	a_r2d->setRenderColour(1.f, 0.f, 1.f, 1.f);
	glm::vec2 jitterPos = circumPos + m_jitterVec;
	a_r2d->drawLine(circumPos.x, circumPos.y, jitterPos.x, jitterPos.y);

	// Final wander direction
	a_r2d->setRenderColour(0.f, 1.f, 0.f, 1.f);
	glm::vec2 wanderPos = m_obj->GetPosition() + m_wanderDir;
	a_r2d->drawLine(m_obj->GetPosition().x, m_obj->GetPosition().y, wanderPos.x, wanderPos.y);

	a_r2d->setRenderColour(0xFFFFFFFF);
#endif
}

void Wander::CalculateWander()
{
	/// WORKING AS INTENDED
	//1. Find random direction by finding a random point on the circumference
	float randAngle = (rand() % RAND_PI_MAX) / 100.f;					// Calculate angle between 0-360 degrees (radians)
	m_randDir = glm::vec2(cosf(randAngle), sinf(randAngle)) * m_radius;	// Constrain random vector within the radius

	//2. Create random vector scaled with jitter
	m_jitterVec = glm::vec2(rand() % (RAND_VEC_MAX - RAND_VEC_MIN) + RAND_VEC_MIN, rand() % (RAND_VEC_MAX - RAND_VEC_MIN) + RAND_VEC_MIN) * m_jitter;

	//3. Calculate wander direction by normalizing calculated wander vector
	m_wanderDir = glm::normalize(m_randDir + m_jitterVec) * m_radius;
	
	//4. Apply projection vector to wander direction
	if (m_obj->GetVelocity() != glm::vec2(0.f, 0.f)) {
		// Modify/project wander direction with the object's normal and scale it by distance
		m_projectedVec = glm::normalize(m_obj->GetVelocity()) * m_dist;		
	}
	else {
		// Velocity is 0, make projection vector zreo to avoid nan errors when adding to vector
		m_projectedVec = glm::vec2(0.f, 0.f);
	}

	m_wanderDir += m_projectedVec;
}
