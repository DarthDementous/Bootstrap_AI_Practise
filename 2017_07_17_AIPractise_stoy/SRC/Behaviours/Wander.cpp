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

Wander::Wander(Seek* a_seek, float a_radius, float a_dist, float a_jitter) :
	m_seek(a_seek), m_radius(a_radius), m_dist(a_dist), m_jitter(a_jitter)
{
}

void Wander::Startup(GameObj* a_obj)
{
	// Make sure seek has the right values
	m_seek->SetStrength(SEEK_STRENGTH);
	m_seek->SetInnerRadius(SEEK_RADIUS);
	m_seek->SetOuterRadius(0);

	// Upon reaching seek target it'll calculate new random wander target
	//m_seek->SetInnerRadiusEnter([this, a_obj]() {
	//	CalculateWanderTarget(a_obj);
	//});

	// Get first wander target
	CalculateWanderTarget(a_obj);
}

void Wander::Update(GameObj* a_obj, float a_dt) {
	// Update seek behaviour so it travels towards current wander target
	m_seek->Update(a_obj, a_dt);

	// Calculate new wander target every interval
	static float timer = WANDER_TIMER;
	
	timer -= a_dt;

	if (timer < 0) {
		CalculateWanderTarget(a_obj);
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
	a_r2d->drawCircle(m_projectedPos.x, m_projectedPos.y, m_radius);

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
	//a_r2d->drawLine(a_obj->GetPosition().x, a_obj->GetPosition().y, m_wanderTarget.x, m_wanderTarget.y);

	a_r2d->setRenderColour(0xFFFFFFFF);
#endif
}

void Wander::CalculateWanderTarget(GameObj* a_obj)
{
	std::default_random_engine randGen(time(NULL));
	std::uniform_real_distribution<float> distribution(0.0f, _2PI);

	m_wanderTarget = a_obj->GetPosition();

	/// WORKING AS INTENDED
	//1. Find random point along the edge of current wander circle by calculating random angle 0-628 and converting back to float (about 360 degrees in radians)
	float randAngle = cosf(distribution(randGen));
	m_randDir = glm::vec2(cosf(randAngle), sinf(randAngle)) * m_radius;
	m_wanderTarget += m_randDir;

	// randNum = ((rand() % 618)-314)/100

	/// WORKING AS INTENDED
	//2. Create randomised vector and scale it with jitter (set magnitude to jitter)
	m_jitterVec = glm::vec2(rand() % (RAND_VEC_MAX - RAND_VEC_MIN) + RAND_VEC_MIN, rand() % (RAND_VEC_MAX - RAND_VEC_MIN) + RAND_VEC_MIN) * m_jitter;
	//m_wanderTarget += m_jitterVec;

	
	//3. Normalize and scale back inside radius after jitter
	//m_wanderTarget = glm::normalize(m_wanderTarget) * m_radius;

	/// WORKING AS INTENDED
	//4. Apply to current object's heading (normalized entity vector) and then scale with specified distance to put target infront
	m_projectedPos = a_obj->GetPosition() + glm::normalize(a_obj->GetVelocity()) * m_dist;

	//5. Turn direction into a target and then set it as the target for the seek behaviour.
	//m_wanderTarget += m_projectedPos;
	
	m_seek->SetTarget(m_wanderTarget);
}
