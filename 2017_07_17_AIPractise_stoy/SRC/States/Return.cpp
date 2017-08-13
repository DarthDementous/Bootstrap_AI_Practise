#include "States/Return.h"
#include "Behaviours/Arrival.h"
#include "Behaviours/CollisionAvoidance.h"
#include "Entities/NPC.h"

Return::Return(IAgent * a_host)
{
	NPC* npc = dynamic_cast<NPC*>(a_host);

	m_arrival = new Arrival(a_host, 100.f, 250.f, [this, npc]() { 
		// Reached home, state no longer valued
		this->SetUtility(0.f);

		// Allow npc to send return messages again
		npc->canSendReturn = true;
	});	
	m_arrival->SetScale(75.f);
	AddBehaviour("ARRIVAL", m_arrival);

	m_collAvoid = new CollisionAvoidance(a_host);
	m_collAvoid->SetScale(25.f);
	AddBehaviour("COLL_AVOID", m_collAvoid);
}

Return::~Return()
{
}

void Return::Startup()
{
	SetBehaviour("ARRIVAL", false);
	SetBehaviour("COLL_AVOID", false);
}

void Return::Update(float a_dt)
{
	AIState::Update(a_dt);
}

void Return::Draw(aie::Renderer2D * a_r2d)
{
	AIState::Draw(a_r2d);
}

void Return::SetTarget(glm::vec2 & a_pos)
{
	m_arrival->SetTarget(a_pos);
}
