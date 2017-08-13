#pragma once

#include "AIState.h"
#include <glm/vec2.hpp>

class Arrival;
class CollisionAvoidance;

/**
*	@brief State that has the agent arrive back at a given point.
*/
class Return : public AIState {
public:
	Return(IAgent* a_host = nullptr);
	virtual ~Return();

	virtual void Startup();
	virtual void Update(float a_dt);
	virtual void Draw(aie::Renderer2D* a_r2d);
	virtual void Shutdown() {}

	void SetTarget(glm::vec2& a_pos);
protected:
	Arrival*				m_arrival = nullptr;			/*Pull the agent in by taking over their velocity until they are at the point.*/
	CollisionAvoidance*		m_collAvoid = nullptr;			/*Attempt to negotiate terrain.*/
private:
};