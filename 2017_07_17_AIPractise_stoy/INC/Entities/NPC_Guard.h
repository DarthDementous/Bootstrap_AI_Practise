#pragma once

#include "NPC.h"

class PathFinder;

/**
*	@brief NPC class that patrols along the grid looking for the player.
*/
class NPC_Guard : public NPC {
public:
	NPC_Guard(glm::vec2 a_pos = glm::vec2(0.f, 0.f), float a_frict = PLAYER_FRICTION, PathFinder* a_pf = nullptr);
	virtual ~NPC_Guard() {}

	virtual void Update(float a_dt);
	virtual void Render(aie::Renderer2D* a_r2d);
protected:
private:
};