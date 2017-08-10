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

	m_behaviourManager = new GameStateManager;
}

IAgent::~IAgent()
{
	delete m_behaviourManager;
}

void IAgent::Update(float a_dt)
{
	m_behaviourManager->Update(a_dt);
	
	/// Physics
	ApplyPhysics(a_dt);
}

void IAgent::Render(aie::Renderer2D * a_r2d)
{
	m_behaviourManager->Draw(a_r2d);

	// Object
	a_r2d->drawCircle(m_pos.x, m_pos.y, PLAYER_RADIUS);

	// Velocity
	a_r2d->setRenderColour(1.f, 1.f, 0.f);
	glm::vec2 targetPt = m_pos + m_vel;
	a_r2d->drawLine(m_pos.x, m_pos.y, targetPt.x, targetPt.y);

	a_r2d->setRenderColour(0xFFFFFFFF);
}

void IAgent::AddBehaviour(const char * a_name, IGameState * a_beh)
{
	m_behaviourManager->PushState(a_name, a_beh);
}

void IAgent::SetBehaviour(const char * a_name, bool a_replace)
{
	if (a_replace) {
		// Remove current active behaviour (crashes if no current behaviours)
		m_behaviourManager->PopState();
	}

	// Add behaviour to active states
	m_behaviourManager->SetState(a_name);
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

