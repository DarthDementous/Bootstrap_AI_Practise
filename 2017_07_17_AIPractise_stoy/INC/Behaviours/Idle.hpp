#pragma once

#include "IBehaviour.h"

/**
*	@brief Default state where object is in a neutral state.
*/
class Idle : public IBehaviour {
public:
	Idle(IAgent* a_obj = nullptr) { m_obj = a_obj; }
	~Idle() {}

	virtual void Startup() {}
	virtual void Update(float a_dt) {}
	virtual void Draw(aie::Renderer2D* a_r2d) {}
	virtual void Shutdown() {}
protected:
private:
};