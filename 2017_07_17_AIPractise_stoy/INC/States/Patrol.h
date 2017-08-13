#pragma once

#include "AIState.h"

class Wander;
class Idle;
class CollisionAvoidance;

/**
*	@brief Move Agent randomly with pauses, taking into account possible collisions.
*/
class Patrol : public AIState {
public:
	Patrol(IAgent* a_host);
	virtual ~Patrol() {}

	virtual void Startup();
	virtual void Update(float a_dt);
	virtual void Draw(aie::Renderer2D* a_r2d);
	virtual void Shutdown() {}
protected:
	Idle*					m_idle;		/*Apply no steering forces.*/
	Wander*					m_wander;	/*Move randomly within a given cone of direction.*/
	CollisionAvoidance*		m_collAvoid;
private:
};