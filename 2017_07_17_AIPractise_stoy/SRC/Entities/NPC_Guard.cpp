#include "Entities/NPC_Guard.h"
#include "Entities/Player.h"
#include "States/PatrolPath.h"
#include "Utility.h"
#include "Blackboard.h"
#include "Behaviours/Wander.h"
#include <GameStateManager.h>
#include <Renderer2D.h>

NPC_Guard::NPC_Guard(glm::vec2 a_pos, float a_frict, PathFinder* a_pf)
{
	m_pos = a_pos;
	m_friction = a_frict;

	PatrolPath* patrolPath = new PatrolPath(this, a_pf);
	patrolPath->SetUtility(50.f);
	m_stateManager->PushState("PATROL", patrolPath);
}

void NPC_Guard::Update(float a_dt)
{
	NPC::Update(a_dt);

	// NPCs are guaranteed to have a wander state
	//Wander* wander = (Wander*)m_behaviourManager->GetState("WANDER");

	// Player is within view radius
	//if (Util::PointVsCircle(m_playerPos, wander->GetWanderCircle()) != eCollisionType::NONE) {
		// Alert other npcs
		//Blackboard::AddMessage(new Blackboard::Message(eMessageType::PLAYER_FOUND, nullptr, this));
	//}


}

void NPC_Guard::Render(aie::Renderer2D * a_r2d)
{
	// Render from IAgent to avoid drawing body for npc as well as npc guard
	IAgent::Render(a_r2d);

	a_r2d->setRenderColour(1.f, 0.f, 1.f);
	a_r2d->drawCircle(m_pos.x, m_pos.y, PLAYER_RADIUS * 2);
	
	a_r2d->setRenderColour(0xFFFFFFFF);
}
