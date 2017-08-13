#include "Entities/NPC.h"
#include <Input.h>
#include "States/AIState.h"
#include <GameStateManager.h>
#include <Renderer2D.h>

NPC::NPC(glm::vec2 a_pos, float a_frict)
{
	m_pos		= a_pos;
	m_friction	= a_frict;
}

NPC::~NPC()
{
}

void NPC::Update(float a_dt)
{
	IAgent::Update(a_dt);
}

void NPC::Render(aie::Renderer2D * a_r2d)
{
	IAgent::Render(a_r2d);

	// Object
	a_r2d->setRenderColour(0.f, 1.f, 1.f);
	a_r2d->drawCircle(m_pos.x, m_pos.y, PLAYER_RADIUS);

	a_r2d->setRenderColour(0xFFFFFFFF);
}

void NPC::DoBestAction()
{
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

	IGameState* topState = m_stateManager->GetTopState();
	
	// There is an active state, make sure its not the same one to avoid spamming the startup function
	if (topState) {
		if (bestAction != topState) {
			m_stateManager->PopState();					// Remove old state so there's only one active state at a time	

			m_stateManager->SetState(bestAction);
		}
	}
	// No active states, set to best one
	else {
		m_stateManager->SetState(bestAction);
	}

#pragma endregion
}
