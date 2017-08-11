#include "Entities/Player.h"
#include "Behaviours/KeyboardController.h"
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

	// Initialise with keyboard behaviour
	AddBehaviour("KEYBOARD", new KeyboardController(this));
	SetBehaviour("KEYBOARD", false);
}

Player::~Player() {
}

void Player::Update(float a_dt)
{
	// Update with base class function
	IAgent::Update(a_dt);

	// Broadcast position to blackboard so npcs can use it
	Blackboard::AddMessage(new Blackboard::Message(eMessageType::POS_REPORT, this, this));
}

void Player::Render(aie::Renderer2D * a_r2d)
{
	// Render with base class function
	IAgent::Render(a_r2d);

	a_r2d->drawCircle(m_pos.x, m_pos.y, PLAYER_RADIUS);
}
