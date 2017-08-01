#include "Behaviours/Wander.h"
#include "Behaviours/Seek.h"
#include <math.h>
#include <MathLib_Utility.h>
#include <glm/gtx/norm.hpp>
#include <Entities/GameObj.h>
#include <Renderer2D.h>
#include <math.h>
#include <random>
#include <ctime>

Wander::Wander(float a_radius, float a_dist, float a_jitter) :
	m_radius(a_radius), m_dist(a_dist), m_jitter(a_jitter)
{
}

void Wander::Startup(GameObj* a_obj)
{
	// Get first wander vector
	CalculateWander(a_obj);
}

void Wander::Update(GameObj* a_obj, float a_dt) {
	// Move in current wander direction
	a_obj->ApplyForce(m_wanderDir);

	// Calculate new wander vector every interval
	static float timer = WANDER_TIMER;
	
	timer -= a_dt;

	if (timer < 0) {
		CalculateWander(a_obj);
		timer = WANDER_TIMER;
	}
}

void Wander::Render(GameObj* a_obj, aie::Renderer2D* a_r2d) {
#ifdef _DEBUG
	// Initial wander target radius
	a_r2d->setRenderColour(0.f, 1.f, 1.f, 0.5f);
	a_r2d->drawCircle(a_obj->GetPosition().x, a_obj->GetPosition().y, m_radius);

	// Projected wander target radius
	a_r2d->setRenderColour(1.f, 1.f, 1.f, 0.5f);
	glm::vec2 projectedPos = a_obj->GetPosition() + m_projectedVec;
	a_r2d->drawCircle(projectedPos.x, projectedPos.y, m_radius);

	// Initial random position on circumference
	a_r2d->setRenderColour(1.f, 0.f, 0.f, 1.f);
	glm::vec2 circumPos = a_obj->GetPosition() + m_randDir;
	a_r2d->drawCircle(circumPos.x, circumPos.y, 4.f);

	// Jitter vector
	a_r2d->setRenderColour(1.f, 0.f, 1.f, 1.f);
	glm::vec2 jitterPos = circumPos + m_jitterVec;
	a_r2d->drawLine(circumPos.x, circumPos.y, jitterPos.x, jitterPos.y);

	// Final wander direction
	a_r2d->setRenderColour(0.f, 1.f, 0.f, 1.f);
	glm::vec2 wanderPos = a_obj->GetPosition() + m_wanderDir;
	a_r2d->drawLine(a_obj->GetPosition().x, a_obj->GetPosition().y, wanderPos.x, wanderPos.y);

	a_r2d->setRenderColour(0xFFFFFFFF);
#endif
}

void Wander::CalculateWander(GameObj* a_obj)
{
	//std::default_random_engine randGen(time(NULL));
	//std::uniform_real_distribution<float> distribution(0.0f, _2PI);

	/// WORKING AS INTENDED
	//1. Find random direction by finding a random point on the circumference
	float randAngle = (rand() % RAND_PI_MAX) / 100.f;					// Calculate angle between 0-360 degrees (radians)
	m_randDir = glm::vec2(cosf(randAngle), sinf(randAngle)) * m_radius;	// Constrain random vector within the radius

	//2. Create random vector scaled with jitter
	m_jitterVec = glm::vec2(rand() % (RAND_VEC_MAX - RAND_VEC_MIN) + RAND_VEC_MIN, rand() % (RAND_VEC_MAX - RAND_VEC_MIN) + RAND_VEC_MIN) * m_jitter;

	//3. Calculate wander direction by normalizing calculated wander vector
	m_wanderDir = glm::normalize(m_randDir + m_jitterVec) * m_radius;
	
	//4. Apply projection vector to wander direction
	m_projectedVec = glm::normalize(a_obj->GetVelocity()) * m_dist;		// Modify/project wander direction with the object's normal and scale it by distance
	m_wanderDir += m_projectedVec;
}
