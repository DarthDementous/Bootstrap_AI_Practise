#pragma once

#include "IBehaviour.hpp"
#include <glm/vec2.hpp>
#include "Utility.h"

class Seek;

class Wander : public IBehaviour {
public:
	Wander(float a_radius = PLAYER_WANDER_RADIUS, float a_dist = PLAYER_WANDER_DIST, float a_jitter = PLAYER_JITTER);
	virtual ~Wander() {}

	void Update(GameObj* a_obj, Seek* a_beh);
	virtual void Render(GameObj* a_obj, aie::Renderer2D* a_r2d);
	
	/**
	*	@brief Calculate next wander point and seek towards it.
	*	@param a_obj is the entity to seek with.
	*	@param a_beh is the seek behaviour.
	*/
	void CalculateWanderTarget(GameObj* a_obj, Seek* a_beh);
protected:
	float m_radius;				/*Size of wander circle*/
	float m_dist;				/*How far the wander circle is infront*/
	float m_jitter;				/*Amount of random range to randomize the wander circle's position*/

	glm::vec2 m_wanderTarget;	/*Position of last wander circle.*/
private:
};