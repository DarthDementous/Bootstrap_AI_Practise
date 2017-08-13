#pragma once

#include "AIState.h"

class KeyboardController;

/**
*	@brief Class for controlling agent with keyboard.
*/
class UserControl : public AIState {
public:
	UserControl(IAgent* a_host);
	virtual ~UserControl();

	virtual void Startup();
	virtual void Update(float a_dt);
	virtual void Draw(aie::Renderer2D* a_r2d);
	virtual void Shutdown() {}
protected:
	KeyboardController* m_controller = nullptr;
private:
};