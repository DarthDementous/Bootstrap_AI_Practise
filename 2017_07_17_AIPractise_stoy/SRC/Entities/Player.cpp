#include "Entities/Player.h"
#include "Behaviours/KeyboardController.h"
#include "Behaviours/Seek.h"
#include <Input.h>
#include "Utility.h"

Player::Player(glm::vec2 & a_pos, glm::vec2 & a_vel, float a_friction, IBehaviour * a_behaviour) :
	GameObj(a_pos, a_vel, a_friction, a_behaviour) // Call base constructor because the parameters pertain to the base class, not the inherited one.
{
	m_seekBehaviour	= new Seek;
	m_seekBehaviour->SetInnerRadiusEnter([this]() {
		SetBehaviour(m_controlBehaviour);
	});
	m_seekBehaviour->SetOuterRadiusExit([this]() {
		SetBehaviour(m_controlBehaviour);
	});
	m_seekBehaviour->IsOwned(true);				   // Belongs to game object, it is responsible for its deletion so that setting behaviour doesn't delete it.

	m_controlBehaviour	= new KeyboardController;
	m_controlBehaviour->IsOwned(true);			   
}

Player::~Player()
{
	delete m_seekBehaviour;
	delete m_controlBehaviour;
}

void Player::Update(float a_dt)
{
	// Call base update function
	GameObj::Update(a_dt);

#pragma region Behavioural mouse input
	aie::Input* input = aie::Input::getInstance();

	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);

	// Seek
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		m_seekBehaviour->SetTarget(glm::vec2(mouseX, mouseY));
		m_seekBehaviour->SetStrength(SEEK_STRENGTH);
		m_seekBehaviour->SetInnerRadius(SEEK_RADIUS);
		m_seekBehaviour->SetOuterRadius(0);

		SetBehaviour(m_seekBehaviour);
	}
	
	// Flee (modified version of seek)
	else if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT)) {
		m_seekBehaviour->SetTarget(glm::vec2(mouseX, mouseY));
		m_seekBehaviour->SetStrength(FLEE_STRENGTH);
		m_seekBehaviour->SetInnerRadius(0);
		m_seekBehaviour->SetOuterRadius(FLEE_RADIUS);

		SetBehaviour(m_seekBehaviour);
	}
	
	// Return control to player while not enacting AI
	if (GetBehaviour() != m_controlBehaviour && !(input->getPressedKeys().empty())) {
		SetBehaviour(m_controlBehaviour);
	}
#pragma endregion
}

void Player::Render(aie::Renderer2D * a_r2d)
{
	// Call base render function
	GameObj::Render(a_r2d);
}
