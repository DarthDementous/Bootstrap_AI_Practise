#include "GameObj.h"
#include "Utility.h"
#include <Renderer2D.h>

GameObj::~GameObj() {}

void GameObj::Update(float a_dt) {
	// Friction
	ApplyForce(m_friction * -m_vel);

	// Update speed for this frame and reset it
	m_vel += m_accel * a_dt;			
	m_accel = glm::vec2(0, 0);

	// Update position
	m_pos += m_vel * a_dt;				
}
void GameObj::Render(aie::Renderer2D* a_r2d) {
	a_r2d->drawCircle(m_pos.x, m_pos.y, PLAYER_RADIUS);
}