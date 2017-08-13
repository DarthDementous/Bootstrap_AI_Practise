#include "Entities/Player.h"
#include "States/UserControl.h"
#include "Behaviours/CollisionAvoidance.h"
#include <glm/vec2.hpp>
#include <GameStateManager.h>
#include <iostream>
#include <Blackboard.h>
#include <Renderer2D.h>

Player::Player(const glm::vec2 & a_pos, float a_friction)
{
	// NOTE: Even though these are base class variables, do not pass them down to base constructor in : or else it won't assign properly.
	m_pos = a_pos;
	m_friction = a_friction;

#pragma region State Initialization
	UserControl* uc = new UserControl(this);
	uc->SetUtility(100.f);
	m_stateManager->PushState("USER_CONTROL", uc);
	m_stateManager->SetState("USER_CONTROL");
#pragma endregion
}

Player::~Player() {
}

void Player::Update(float a_dt)
{
	// Update with base class function
	IAgent::Update(a_dt);

	// Broadcast position to blackboard so npcs can use it
	Blackboard::AddMessage(new Blackboard::Message(eMessageType::POS_REPORT, this, "PLAYER"));
}

void Player::Render(aie::Renderer2D * a_r2d)
{
	// Render with base class function
	IAgent::Render(a_r2d);

	a_r2d->drawCircle(m_pos.x, m_pos.y, PLAYER_RADIUS);
}
