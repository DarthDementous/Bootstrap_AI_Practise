#include "Entities/Player.h"
#include "Behaviours/KeyboardController.h"
#include <glm/vec2.hpp>
#include <GameStateManager.h>
#include <iostream>

Player::Player(const glm::vec2 & a_pos, float a_friction) :
	IAgent(a_pos, a_friction)	// Call base constructor because the parameters pertain to the base class, not the inherited one.
{
	std::cout << m_pos.x << " " << m_pos.y << std::endl;
	// Initialise with keyboard behaviour
	AddBehaviour("KEYBOARD", new KeyboardController(this));
}

Player::~Player() {
}

void Player::Update(float a_dt)
{
	// Update with base class function
	IAgent::Update(a_dt);

	aie::Input* input = aie::Input::getInstance();

	// Set movement behaviour
	if (input->wasKeyPressed(aie::INPUT_KEY_P)) {
		SetBehaviour("KEYBOARD", false);
	}
}

void Player::Render(aie::Renderer2D * a_r2d)
{
	// Render with base class function
	IAgent::Render(a_r2d);
}
