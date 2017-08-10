#pragma once

#include "Entities/IAgent.h"
#include <glm/vec2.hpp>

class NPC : public IAgent {
public:
	NPC(glm::vec2 a_pos = glm::vec2(0.f, 0.f), float a_frict = PLAYER_FRICTION);
	virtual ~NPC();

	virtual void Update(float a_dt);
	virtual void Render(aie::Renderer2D* a_r2d);
protected:
private:
};