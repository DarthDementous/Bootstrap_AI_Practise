#pragma once

#include "IBehaviour.hpp"
#include <glm/vec2.hpp>
#include "Utility.h"

class Seek;

class Wander : public IBehaviour {
public:
	Wander(float a_radius = PLAYER_WANDER_RADIUS, float a_dist = PLAYER_WANDER_DIST, float a_jitter = PLAYER_JITTER);
	virtual ~Wander() {}

	void Startup(GameObj* a_obj);
	virtual void Update(GameObj* a_obj, float a_dt);
	virtual void Render(GameObj* a_obj, aie::Renderer2D* a_r2d);
	
	/**
	*	@brief Calculate next wander vector.
	*	@param a_obj is the entity to seek with.
	*/
	void CalculateWander(GameObj* a_obj);
protected:
	float m_radius;				/*Size of wander circle*/
	float m_dist;				/*How far the wander circle is infront*/
	float m_jitter;				/*Random modifier applied to wander target*/

	glm::vec2 m_projectedVec;	/*How to project wander vector.*/
	glm::vec2 m_wanderDir;		/*Current wander vector.*/
	glm::vec2 m_jitterVec;		/*Jitter modifier on wander vector.*/
	glm::vec2 m_randDir;		/*Initial random direction from random point on circumference.*/
private:
};