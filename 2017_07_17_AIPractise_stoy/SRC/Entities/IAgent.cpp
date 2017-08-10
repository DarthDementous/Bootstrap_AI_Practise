#include "Entities/IAgent.h"
#include "Behaviours/Seek.h"
#include "Obstacles/IObstacle.h"
#include <GameStateManager.h>
#include <Input.h>
#include <vector>
#include <Renderer2D.h>
#include <iostream>

IAgent::IAgent(const glm::vec2 & a_pos, float a_friction) : GameObj(a_pos), m_friction(a_friction)
{
	std::cout << m_pos.x << " " << m_pos.y << std::endl;
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

	/// Debugging behaviour manager with keyboard input
#ifdef _DEBUG
#pragma region Behavioural mouse input
	aie::Input* input = aie::Input::getInstance();

	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);

	/// Left click
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		//// Seek (only activates if there's no other button combinations)
		if (!input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT) && !input->isKeyDown(aie::INPUT_KEY_LEFT_ALT)) {
			// Dynamically cast so we can access state like seek behaviour
			Seek* seek = dynamic_cast<Seek*>(m_behaviourManager->GetState("SEEK"));

			seek->SetTarget(glm::vec2(mouseX, mouseY));
			seek->SetStrength(SEEK_STRENGTH);
			seek->SetInnerRadius(SEEK_RADIUS);
			seek->SetOuterRadius(0);

			// Set as active behaviour (if already active behaviour will run startup again but not add it to active states again)
			m_behaviourManager->SetState("SEEK");
		}
	}

	///// Right click
	//if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT)) {
	//	//// Flee (modified version of seek)
	//	m_seekBehaviour->SetTarget(glm::vec2(mouseX, mouseY));
	//	m_seekBehaviour->SetStrength(FLEE_STRENGTH);
	//	m_seekBehaviour->SetInnerRadius(0);
	//	m_seekBehaviour->SetOuterRadius(FLEE_RADIUS);

	//	SetBehaviour(m_seekBehaviour);
	//}

	///// Clear path
	//if (input->wasKeyPressed(aie::INPUT_KEY_C)) {
	//	// Reset start and goal nodes to allow for new selection
	//	m_startNode = nullptr;
	//	m_goalNode = nullptr;
	//	// Reset path
	//	m_path->Clear();

	//	// Relinquish control back to player
	//	SetBehaviour(m_controlBehaviour);
	//}

	///// Wander
	//if (input->wasKeyPressed(aie::INPUT_KEY_X)) {
	//	// Set to wander if not already
	//	if (m_behaviour != m_wanderBehaviour) {
	//		SetBehaviour(m_wanderBehaviour);
	//		m_wanderBehaviour->Startup(this);
	//	}
	//}

	///// Arrival
	//if (input->wasKeyPressed(aie::INPUT_KEY_V)) {
	//	m_arrivalBehaviour->SetTarget(glm::vec2(mouseX, mouseY));

	//	// Set to arrival if not already
	//	if (m_behaviour != m_arrivalBehaviour) {
	//		SetBehaviour(m_arrivalBehaviour);
	//	}
	//}

	///// Collision Avoidance
	//if (input->wasKeyPressed(aie::INPUT_KEY_B)) {
	//	if (m_behaviour != m_collisionBehaviour) {
	//		SetBehaviour(m_collisionBehaviour);
	//	}
	//}

	////#ifdef _DEBUG
	////	// Keep searching until goal is reached or all nodes have been searched
	////	if (!m_pathFinder->IsSearchFinished() && input->wasKeyPressed(aie::INPUT_KEY_SPACE)) {
	////		m_pathFinder->ContinuePathSearch();
	////	}
	////#endif
#pragma endregion
#endif
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

