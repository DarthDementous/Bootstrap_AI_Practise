#pragma once

#include "IBehaviour.hpp"
#include <glm/vec2.hpp>
#include "Utility.h"

class Seek;

class Wander : public IBehaviour {
public:
	Wander(GameObj* a_obj = nullptr, float a_radius = PLAYER_WANDER_RADIUS, float a_dist = PLAYER_WANDER_DIST, float a_jitter = PLAYER_JITTER) :
		IBehaviour(a_obj), m_radius(a_radius), m_dist(a_dist), m_jitter(a_jitter) {}
	virtual ~Wander() {}

	virtual void Initialise() {}
	virtual void Startup();
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void Shutdown() {}
	
	/**
	*	@brief Calculate next wander vector.
	*	@param a_obj is the entity to seek with.
	*/
	void CalculateWander();
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