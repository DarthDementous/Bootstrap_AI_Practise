#include "Entities/NPC_Minion.h"
#include "Behaviours/Seek.h"
#include "States/Patrol.h"
#include "States/Converge.h"
#include "States/Return.h"
#include "Blackboard.h"
#include <GameStateManager.h>

NPC_Minion::NPC_Minion(glm::vec2 a_pos, float a_frict)
{
	m_pos		= a_pos;
	m_friction	= a_frict;

#pragma region State initialization
	// Default state, move randomly around the map
	Patrol* patrol = new Patrol(this);
	patrol->SetUtility(25.f);				// Constantly weighted low		

	m_stateManager->PushState("PATROL", patrol);

	// Triggered when player is spotted, move towards the guard that spotted them
	m_stateManager->PushState("CONVERGE", new Converge(this));

	// Triggered after player found message expires, return to arbitrary point
	Return* rt = new Return(this);
	rt->SetTarget(HOME_POS);
	m_stateManager->PushState("RETURN", rt);
#pragma endregion
}

NPC_Minion::~NPC_Minion()
{
}

void NPC_Minion::Update(float a_dt)
{
	// Update state manager
	NPC::Update(a_dt);

	// Reset utility of converge so its only valuable when receiving messages from guard
	Converge* converge = (Converge*)m_stateManager->GetState("CONVERGE");
	converge->SetUtility(0.f);

	// Use information from blackboard to determine utility scores for states
#pragma region Message Receival (must come before base class Update)
	std::vector<Blackboard::Message*> msgs;
	Blackboard::GetMessages(msgs);

	for (auto msg : msgs) {
		// Guard has found player
		if (msg->type == eMessageType::PLAYER_FOUND && msg->author == "GUARD") {
			// Converge on guard
			Converge* converge = (Converge*)m_stateManager->GetState("CONVERGE");
			converge->GetSeek()->SetTarget(msg->content->GetPosition());

			// Immediate priority is to converge, but...
			converge->SetUtility(100.f);
			// ...Weight return high so when message expires, minions go back home
			Return* ret = (Return*)m_stateManager->GetState("RETURN");
			ret->SetUtility(50.f);
		}
	}
#pragma endregion

	// If returning, alert guards once to begin patrolling again
	Return* ret = (Return*)m_stateManager->GetState("RETURN");
	if (m_stateManager->GetTopState() == ret && canSendReturn) {
		Blackboard::AddMessage(new Blackboard::Message(eMessageType::RETURNING, nullptr, "MINION", 5.0, "GUARD"));
		
		// Make sure return message is sent only once per return
		canSendReturn = false;
	}

	DoBestAction();
}

void NPC_Minion::Render(aie::Renderer2D * a_r2d)
{
	// Draw state manager
	NPC::Render(a_r2d);
}
