#include "Behaviours\KeyboardController.h"
#include "Entities/GameObj.h"

KeyboardController::~KeyboardController()
{
}

void KeyboardController::Update(float a_dt)
{
	aie::Input* input = aie::Input::getInstance();
	
	// Input
	if (input->isKeyDown(m_upKey)) {
		m_obj->ApplyForce(glm::vec2(0, PLAYER_FORCE));
	}

	if (input->isKeyDown(m_downKey)) {
		m_obj->ApplyForce(glm::vec2(0, -PLAYER_FORCE));
	}

	if (input->isKeyDown(m_leftKey)) {
		m_obj->ApplyForce(glm::vec2(-PLAYER_FORCE, 0));
	}

	if (input->isKeyDown(m_rightKey)) {
		m_obj->ApplyForce(glm::vec2(PLAYER_FORCE, 0));
	}

}
