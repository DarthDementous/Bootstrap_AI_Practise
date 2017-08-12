#pragma once

#include "IBehaviour.h"
#include "Utility.h"
#include <functional>
#include <glm/vec2.hpp>

/**
*	@brief Behaviour that makes an object go towards a destination and slow down to a stop when within a certain radius.
*/
class Arrival : public IBehaviour {
public:
	Arrival(IAgent* a_obj = nullptr, float a_strength = SEEK_STRENGTH, float a_radius = FLEE_RADIUS, std::function<void()> a_onReachPointFunc = {}) :
		IBehaviour(a_obj), m_strength(a_strength), m_radius(a_radius), m_onReachPointFunc(a_onReachPointFunc) {
	}

	~Arrival();

	virtual void Startup() {}
	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D* a_r2d);
	virtual void Shutdown() {}

	void SetTarget(glm::vec2 a_pos) { m_targetPos = a_pos; }
protected:
	glm::vec2 m_targetPos;		
	glm::vec2 m_lastPos;		/*Position of object last frame.*/

	float m_radius;		/*Size of radius to start slowing down object.*/
	float m_strength;	/*Modifier of force applied to object towards destination.*/

	std::function<void()> m_onReachPointFunc;		/*Call once upon reaching specified point.*/
private:
};