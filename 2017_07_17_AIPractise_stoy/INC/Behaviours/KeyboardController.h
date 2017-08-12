#pragma once

#include "Behaviours\IBehaviour.h"
#include <Input.h>

/**
*	@brief Behaviour that handles movement via player input.
*/
class KeyboardController : public IBehaviour {
public:
	KeyboardController(IAgent* a_obj = nullptr, int a_upKey = 0, int a_downKey = 0, int a_leftKey = 0, int a_rightKey = 0) :
		IBehaviour(a_obj), m_upKey(a_upKey), m_downKey(a_downKey), m_leftKey(a_leftKey), m_rightKey(a_rightKey) {
		
		// If not custom-bound, set to default WASD config
		if (m_upKey == 0) { m_upKey = aie::INPUT_KEY_W; }
		if (m_downKey == 0) { m_downKey = aie::INPUT_KEY_S; }
		if (m_leftKey == 0) { m_leftKey = aie::INPUT_KEY_A; }
		if (m_rightKey == 0) { m_rightKey = aie::INPUT_KEY_D; }

	}
	virtual ~KeyboardController();

	virtual void Startup() {}
	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D* a_r2d) {}
	virtual void Shutdown() {}

	int GetUpKey() { return m_upKey; }
	int GetDownKey() { return m_downKey; }
	int GetLeftKey() { return m_leftKey; }
	int GetRightKey() { return m_rightKey; }

	int SetUpKey(int a_upKey) { m_upKey = a_upKey; }
	int SetDownKey(int a_downKey) { m_downKey = a_downKey; }
	int SetLeftKey(int a_leftKey) { m_rightKey = a_leftKey; }
	int SetRightKey(int a_rightKey) { m_rightKey = a_rightKey; }

protected:
	int m_upKey;
	int m_downKey;
	int m_leftKey;
	int m_rightKey;
private:
};