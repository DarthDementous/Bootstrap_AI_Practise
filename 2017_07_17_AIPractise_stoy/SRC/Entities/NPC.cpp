#include "Entities/NPC.h"
#include "Entities/Player.h"
#include <Input.h>
#include "Behaviours/Wander.h"
#include "Behaviours/Seek.h"
#include <GameStateManager.h>
#include <Renderer2D.h>
#include "Blackboard.h"

NPC::NPC(glm::vec2 a_pos, float a_frict)
{
	m_pos		= a_pos;
	m_friction	= a_frict;

	AddBehaviour("WANDER", new Wander(this));

	Seek* seek = new Seek(this, SEEK_RADIUS);
	seek->SetInnerRadiusEnter([this]() { this->SetBehaviour("WANDER", true); });
	AddBehaviour("SEEK", seek);

	// Initialize to use wander behaviour
	SetBehaviour("WANDER", false);
}

NPC::~NPC()
{
}

void NPC::Update(float a_dt)
{
	IAgent::Update(a_dt);
	
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
			// Converge near player
			Seek* seek = (Seek*)m_behaviourManager->GetState("SEEK");
			seek->SetTarget(m_playerPos);
			seek->SetStrength(SEEK_STRENGTH);

			SetBehaviour("SEEK", true);			// Replace wander behaviour
		}
	}
#pragma endregion
}

void NPC::Render(aie::Renderer2D * a_r2d)
{
	IAgent::Render(a_r2d);

	// Object
	a_r2d->setRenderColour(0.f, 1.f, 1.f);
	a_r2d->drawCircle(m_pos.x, m_pos.y, PLAYER_RADIUS);

	a_r2d->setRenderColour(0xFFFFFFFF);
}
