#include "Entities/IAgent.h"
#include "Behaviours/Seek.h"
#include "Obstacles/IObstacle.h"
#include <GameStateManager.h>
#include <Input.h>
#include <vector>
#include <Renderer2D.h>
#include <iostream>

IAgent::IAgent(const glm::vec2 & a_pos, float a_friction) : m_friction(a_friction)
{
	m_pos = a_pos;

	m_stateManager = new GameStateManager;
}

IAgent::~IAgent()
{
	delete m_stateManager;
}

void IAgent::Update(float a_dt)
{	
	/// Physics
	ApplyPhysics(a_dt);

	// Update active states
	m_stateManager->Update(a_dt);
}

void IAgent::Render(aie::Renderer2D * a_r2d)
{	
	// Draw active states
	m_stateManager->Draw(a_r2d);

	// Velocity
#ifdef _DEBUG
	a_r2d->setRenderColour(1.f, 1.f, 0.f);
	glm::vec2 targetPt = m_pos + m_vel;
	a_r2d->drawLine(m_pos.x, m_pos.y, targetPt.x, targetPt.y);
#endif

	a_r2d->setRenderColour(0xFFFFFFFF);
}


void IAgent::ApplyPhysics(float a_dt)
{
	// Friction
	ApplyForce(m_friction * -m_vel);

	// Update speed for this frame and reset it
	m_vel += m_accel * a_dt;
	m_accel = glm::vec2(0, 0);

	// Update position
	m_pos += m_vel * a_dt;
}

void IAgent::SetObstacles(std::vector<IObstacle*> a_obs)
{
	for (auto obstacle : m_obstacles) {
		delete obstacle;				/*Clear dynamically allocated memory.*/
	}

	m_obstacles = a_obs;
}

