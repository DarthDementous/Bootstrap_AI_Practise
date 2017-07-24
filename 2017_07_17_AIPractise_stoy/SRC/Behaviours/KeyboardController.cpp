#include "Behaviours\KeyboardController.h"
#include "Entities/GameObj.h"

KeyboardController::~KeyboardController()
{
}

void KeyboardController::Update(GameObj * a_obj, float a_dt)
{
	aie::Input* input = aie::Input::getInstance();
	
	// Input
	if (input->isKeyDown(m_upKey)) {
		a_obj->ApplyForce(glm::vec2(0, 1000));
	}

	if (input->isKeyDown(m_downKey)) {
		a_obj->ApplyForce(glm::vec2(0, -1000));
	}

	if (input->isKeyDown(m_leftKey)) {
		a_obj->ApplyForce(glm::vec2(-1000, 0));
	}

	if (input->isKeyDown(m_rightKey)) {
		a_obj->ApplyForce(glm::vec2(1000, 0));
	}

}
