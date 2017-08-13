#include "States\Patrol.h"
#include "Behaviours\Idle.hpp"
#include "Behaviours/Wander.h"
#include "Behaviours/CollisionAvoidance.h"

Patrol::Patrol(IAgent * a_host)
{
	m_idle = new Idle(a_host);
	AddBehaviour("IDLE", m_idle);

	m_wander = new Wander(a_host);
	AddBehaviour("WANDER", m_wander);

	m_collAvoid = new CollisionAvoidance(a_host);
	AddBehaviour("COLL_AVOID", m_collAvoid);
}

void Patrol::Startup()
{
	m_wander->SetScale(25.f);
	SetBehaviour(m_wander, false);

	m_collAvoid->SetScale(75.f);
	SetBehaviour(m_collAvoid, false);
}

void Patrol::Update(float a_dt)
{
	AIState::Update(a_dt);
	//// Negate wandering force after a certain interval
	//static float timer = WANDER_INTERVAL;
	//timer -= a_dt;

	//if (timer < 0.f) {
	//	// Interval reached, normal wander force scale for one frame
	//	m_wander->SetScale(50.f);
	//}
	//// Interval not reached, don't activate wander yet
	//else {
	//	m_wander->SetScale(0.f);
	//}
}

void Patrol::Draw(aie::Renderer2D * a_r2d)
{
	AIState::Draw(a_r2d);
}
