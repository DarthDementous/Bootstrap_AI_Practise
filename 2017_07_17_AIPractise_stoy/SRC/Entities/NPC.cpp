#include "Entities/NPC.h"
#include "Entities/Player.h"
#include <Input.h>
#include "States/Converge.h"
#include "Behaviours/Seek.h"
#include <GameStateManager.h>
#include <Renderer2D.h>
#include "Blackboard.h"

NPC::NPC(glm::vec2 a_pos, float a_frict)
{
	m_pos		= a_pos;
	m_friction	= a_frict;

#pragma region State initialization
	m_stateManager->PushState("CONVERGE", new Converge(this));
#pragma endregion
}

NPC::~NPC()
{
}

void NPC::Update(float a_dt)
{
	IAgent::Update(a_dt);
	
	// Use information from blackboard to determine utility scores for states
#pragma region Message Receival
	std::vector<Blackboard::Message*> msgs;
	Blackboard::GetMessages(msgs);

	for (auto msg : msgs) {
		if (msg->type == eMessageType::POS_REPORT) {
			Player* player = dynamic_cast<Player*>(msg->author);

			// Update player position
			if (player) {
				m_playerPos = player->GetPosition();
			}
		}
		else if (msg->type == eMessageType::PLAYER_FOUND) {
			// Converge on player
			Converge* converge = (Converge*)m_stateManager->GetState("CONVERGE");
			converge->GetSeek()->SetTarget(m_playerPos);
			
			converge->SetUtility(100.f);
		}
	}
#pragma endregion

#if 1
#pragma region Decide Action with Best Utility
	AIState* bestAction = (AIState*)m_stateManager->GetStates()[0];	// Start at first possible behaviour (guaranteed to be at least one)

	// Find the state with the highest utility score
	for (auto state : m_stateManager->GetStates()) {
		AIState* ai_state = (AIState*)state;

		// State has a higher utility score
		if (ai_state->GetUtility() > bestAction->GetUtility()) {
			// Update best action
			bestAction = ai_state;
		}
	}

	auto activeStates = m_stateManager->GetActiveStates();
	auto foundState = std::find(activeStates.begin(), activeStates.end(), bestAction);

	// Change state to best rated one ONLY if its not a currently active state to avoid it spamming the start-up function
	if (foundState == activeStates.end()) {			
		m_stateManager->SetState(bestAction);
	}
	
#pragma endregion
#endif
}

void NPC::Render(aie::Renderer2D * a_r2d)
{
	IAgent::Render(a_r2d);

	// Object
	a_r2d->setRenderColour(0.f, 1.f, 1.f);
	a_r2d->drawCircle(m_pos.x, m_pos.y, PLAYER_RADIUS);

	a_r2d->setRenderColour(0xFFFFFFFF);
}
