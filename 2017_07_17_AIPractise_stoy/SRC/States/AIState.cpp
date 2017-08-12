#include "States/AIState.h"
#include <GameStateManager.h>
#include "Behaviours/IBehaviour.h"

AIState::AIState(IAgent * a_host)
{
	m_behaviourManager = new GameStateManager;
}

AIState::~AIState()
{
	delete m_behaviourManager;
}

void AIState::Update(float a_dt)
{
	// Update active behaviours
	m_behaviourManager->Update(a_dt);
}

void AIState::Draw(aie::Renderer2D * a_r2d)
{
	// Draw active behaviours
	m_behaviourManager->Draw(a_r2d);
}

void AIState::SetBehaviour(const char * a_name, bool a_replace)
{
	if (a_replace) {
		// Remove current active behaviour (crashes if no current behaviours)
		m_behaviourManager->PopState();
	}

	// Add behaviour to active states
	m_behaviourManager->SetState(a_name);
}

void AIState::SetBehaviour(IBehaviour * a_beh, bool a_replace)
{
	if (a_replace) {
		// Remove current active behaviour (crashes if no current behaviours)
		m_behaviourManager->PopState();
	}

	// Add behaviour to active states
	m_behaviourManager->SetState(a_beh);
}


void AIState::AddBehaviour(const char * a_name, IGameState * a_beh)
{
	m_behaviourManager->PushState(a_name, a_beh);
}
