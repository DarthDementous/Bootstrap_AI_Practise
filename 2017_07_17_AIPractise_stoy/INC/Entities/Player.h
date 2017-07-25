#pragma once

#include "GameObj.h"

class Seek;
class KeyboardController;

/**
*	@brief Entity designed to represent the user in the game space that inherits from the GameObj interface class.
*/
class Player : public GameObj {
public:
	Player(glm::vec2& a_pos = glm::vec2(0, 0), glm::vec2& a_vel = glm::vec2(0, 0), float a_friction = PLAYER_FRICTION, IBehaviour* a_behaviour = nullptr);			
	virtual ~Player();

	virtual void Update(float a_dt);
	virtual void Render(aie::Renderer2D* a_r2d);
protected:
	//Hold onto variable for each wanted behaviour to avoid initialising once every update frame
	Seek*					m_seekBehaviour		= nullptr;								
	KeyboardController*		m_controlBehaviour	= nullptr;
private:
};