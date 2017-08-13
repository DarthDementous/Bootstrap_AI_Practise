#include "States/UserControl.h"
#include "Behaviours\KeyboardController.h"

UserControl::UserControl(IAgent * a_host)
{
#pragma region Behaviour Initialisation
	m_controller = new KeyboardController(a_host);
	AddBehaviour("CONTROLLER", m_controller);
#pragma endregion
}

UserControl::~UserControl()
{
}

void UserControl::Startup()
{
	SetBehaviour("CONTROLLER", false);
}

void UserControl::Update(float a_dt)
{
	AIState::Update(a_dt);
}

void UserControl::Draw(aie::Renderer2D * a_r2d)
{
	AIState::Draw(a_r2d);
}
