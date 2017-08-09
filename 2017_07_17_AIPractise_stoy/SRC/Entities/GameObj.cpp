#include "Entities/GameObj.h"
#include "Utility.h"
#include <Renderer2D.h>
#include "Behaviours/IBehaviour.hpp"
#include "Obstacles/IObstacle.h"

GameObj::GameObj(glm::vec2 & a_pos, glm::vec2 & a_vel, float a_friction) : m_pos(a_pos), m_vel(a_vel), m_friction(a_friction) {
	// Set ownership if there is a behaviour assigned
	if (m_behaviour) {
		m_behaviour->IsOwned(true);
	}
}

GameObj::~GameObj() {
}

void GameObj::Update(float a_dt) {
	MovementPhysics(a_dt);
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
