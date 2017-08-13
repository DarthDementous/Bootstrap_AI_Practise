#include "Entities/NPC_Guard.h"
#include "Entities/Player.h"
#include "States/PatrolPath.h"
#include "Utility.h"
#include "Blackboard.h"
#include "Behaviours/Wander.h"
#include "Behaviours/CollisionAvoidance.h"
#include <GameStateManager.h>
#include <Renderer2D.h>

NPC_Guard::NPC_Guard(glm::vec2& a_pos, float a_frict, PathFinder* a_pf, Graph2D::Node* a_startNode)
{
	m_pos = a_pos;			
	m_friction = a_frict;

#pragma region State Initialization
	// Default state, move back and forth along randomly generated path looking for player
	PatrolPath* patrolPath = new PatrolPath(this, a_pf, a_startNode);
	patrolPath->SetUtility(25.f);							// Constantly weighted low
	patrolPath->GetCollAvoid()->SetLOSLength(LOS_LENGTH / 2);
	m_stateManager->PushState("PATROL_PATH", patrolPath);

	// Do nothing while waiting for minions to arrive
	AIState* wait = new AIState(this);
	m_stateManager->PushState("WAIT", wait);
#pragma endregion
}

void NPC_Guard::Update(float a_dt)
{
	NPC::Update(a_dt);

#pragma region Check Blackboard Messages
	std::vector<Blackboard::Message*> msgs;
	Blackboard::GetMessages(msgs);

	for (auto msg : msgs) {
		// Report of position from player
		if (msg->type == POS_REPORT && msg->author == "PLAYER") {
			// Update player position
			PatrolPath* pp = (PatrolPath*)m_stateManager->GetState("PATROL_PATH");
			pp->SetCheckPos(msg->content->GetPosition());
		}

		// Minions are returning
		if (msg->type == RETURNING && msg->target == "GUARD") {
			// Weight so guard patrols again
			AIState* wait = (AIState*)m_stateManager->GetState("WAIT");
			wait->SetUtility(0.f);
		}
	}
		

#pragma endregion

	// If patrolling, check if player has been located
	PatrolPath* pp = (PatrolPath*)m_stateManager->GetState("PATROL_PATH");

	if (m_stateManager->GetTopState() == pp) {
		// Player spotted, alert minions to converge on guard's position
		if (pp->IsIntruderSpotted()) {
			Blackboard::AddMessage(new Blackboard::Message(eMessageType::PLAYER_FOUND, this, "GUARD", FOUND_TIMER));

			// Idle while minions converge so player found message doesn't get sent more than once
			AIState* wait = (AIState*)m_stateManager->GetState("WAIT");
			wait->SetUtility(50.f);
		}
	}

	DoBestAction();
}

void NPC_Guard::Render(aie::Renderer2D * a_r2d)
{
	// Render from IAgent to avoid drawing body for npc as well as npc guard
	IAgent::Render(a_r2d);

	a_r2d->setRenderColour(0xFFD700FF);	// Gold
	a_r2d->drawCircle(m_pos.x, m_pos.y, PLAYER_RADIUS * 2);
	
	a_r2d->setRenderColour(0xFFFFFFFF);
}
