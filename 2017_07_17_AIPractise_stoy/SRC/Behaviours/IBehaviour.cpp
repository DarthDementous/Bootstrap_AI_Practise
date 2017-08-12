#include "Behaviours\IBehaviour.h"
#include "Entities/IAgent.h"
#include <GameStateManager.h>
#include "States/AIState.h"

float IBehaviour::GetScaleFactor()
{
	float scaleSum = 0.f;

	// Go through every currently active state in object and add up score of possible behaviours in each
	for (auto state : m_obj->GetStateManager()->GetActiveStates()) {
		AIState* ai_state = (AIState*)state;

		for (auto beh_state : ai_state->GetBehaviourManager()->GetStates()) {
			IBehaviour* beh = (IBehaviour*)beh_state;

			scaleSum += beh->m_scale;						// Same class means they are friends, private/protected members accessible.
		}	
	}

	// Return normalized utility
	return m_scale / scaleSum;
}
