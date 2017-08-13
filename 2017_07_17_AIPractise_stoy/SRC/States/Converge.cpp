#include "States/Converge.h"
#include "Entities/IAgent.h"
#include "Behaviours/Seek.h"
#include "Behaviours/CollisionAvoidance.h"
#include <GameStateManager.h>

Converge::Converge(IAgent * a_host)
{
#pragma region Behaviour initialization
	m_seek = new Seek(a_host, SEEK_RADIUS);
	m_seek->SetStrength(SEEK_STRENGTH);
	m_seek->SetScale(75.f);
	AddBehaviour("SEEK", m_seek);

	m_collAvoid = new CollisionAvoidance(a_host);
	m_collAvoid->SetScale(50.f);
	AddBehaviour("COLL_AVOID", m_collAvoid);
#pragma endregion
}

Converge::~Converge()
{
}

void Converge::Startup()
{
	// Two active behaviours, seek and collision avoidance, that are weighted
	SetBehaviour("SEEK", false);
	SetBehaviour("COLL_AVOID", false);
}

void Converge::Update(float a_dt)
{
	// Call base class update (behaviours)
	AIState::Update(a_dt);
}

void Converge::Draw(aie::Renderer2D * a_r2d)
{
	// Call base class draw (behaviours)
	AIState::Draw(a_r2d);
}
