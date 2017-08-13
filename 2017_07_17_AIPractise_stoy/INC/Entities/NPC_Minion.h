#pragma once

#include "NPC.h"

/**
*	@brief NPC type that responds to guards.
*/
class NPC_Minion : public NPC {
public:
	NPC_Minion(glm::vec2 a_pos = glm::vec2(0.f, 0.f), float a_frict = PLAYER_FRICTION);
	virtual ~NPC_Minion();

	virtual void Update(float a_dt);
	virtual void Render(aie::Renderer2D* a_r2d);
protected:
private:
	
};