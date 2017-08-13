#pragma once

#include "Entities/IAgent.h"
#include <glm/vec2.hpp>

class NPC : public IAgent {
public:
	NPC(glm::vec2 a_pos = glm::vec2(0.f, 0.f), float a_frict = PLAYER_FRICTION);
	virtual ~NPC();

	/**
	*	@brief Update active states. (NOTE: Inherited classes must call this FIRST in their Update)
	*	@param a_dt is the time between frames used to normalize calculations.
	*	@return void.
	*/
	virtual void Update(float a_dt);
	virtual void Render(aie::Renderer2D* a_r2d);
public:
	bool canSendReturn = true;					// Limit npc ability to send one return message to avoid spamming the blackboard.
protected:
	/**
	*	@brief Find state with the highest utility score and perform it. (NOTE: Must be done LAST in update after setting state utilities)*
	*	@return void.
	*/
	void DoBestAction();
private:
};