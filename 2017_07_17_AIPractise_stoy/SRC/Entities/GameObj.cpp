#include "Entities/GameObj.h"
#include "Utility.h"
#include <Renderer2D.h>
#include "Behaviours/IBehaviour.hpp"

GameObj::~GameObj() {
	delete m_behaviour;
}

void GameObj::Update(float a_dt) {
#pragma region Behaviour
	if (m_behaviour) {
		m_behaviour->Update(this, a_dt);
	}
#pragma endregion

#pragma region Movement
	MovementPhysics(a_dt);
#pragma endregion
}
void GameObj::Render(aie::Renderer2D* a_r2d) {
	// Calculate point of destination
	glm::vec2 targetHeading = m_pos + m_vel;

	a_r2d->drawCircle(m_pos.x, m_pos.y, PLAYER_RADIUS);

	// Draw line to destination
	a_r2d->setRenderColour(0xFF7F00FF);
	a_r2d->drawLine(m_pos.x, m_pos.y, targetHeading.x, targetHeading.y);
	a_r2d->setRenderColour(0xFFFFFFFF);
}

void GameObj::MovementPhysics(float a_dt)
{
	// Friction
	ApplyForce(m_friction * -m_vel);

	// Update speed for this frame and reset it
	m_vel += m_accel * a_dt;
	m_accel = glm::vec2(0, 0);

	// Update position
	m_pos += m_vel * a_dt;
}

void GameObj::SetBehaviour(IBehaviour * a_behaviour)
{
	// Delete previous behaviour
	delete m_behaviour;

	m_behaviour = a_behaviour;
}
