#pragma once

#include "IAgent.h"
#include "Graph/Graph2D.h"

/**
*	@brief Entity designed to represent the user in the game space that inherits from the Agent interface class.
*/
class Player : public IAgent {
public:
	Player(const glm::vec2& a_pos = glm::vec2(0.f, 0.f), float a_friction = PLAYER_FRICTION);
	virtual ~Player();

	virtual void Update(float a_dt);
	virtual void Render(aie::Renderer2D* a_r2d);
protected:
private:
};