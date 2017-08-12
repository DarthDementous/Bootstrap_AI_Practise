#pragma once

#include "AIState.h"

class Seek;
class CollisionAvoidance;

/**
*	@brief Move Agent towards a given target, taking obstacles into account.
*/
class Converge : public AIState {
public:
	Converge(IAgent* a_host = nullptr);
	virtual ~Converge();

	virtual void Startup();
	virtual void Update(float a_dt);
	virtual void Draw(aie::Renderer2D* a_r2d);
	virtual void Shutdown() {}

	/**
	*	@brief Get the seek behaviour.
	*	@return Pointer to seek (can be modified).
	*/
	Seek* GetSeek() { return m_seek; }
protected:
	// Keep hold of behaviour pointers as member variables for easy access (NOTE: Behaviours owned by manager, not the state)
	Seek*				m_seek = nullptr;
	CollisionAvoidance* m_collAvoid = nullptr;
private:
};