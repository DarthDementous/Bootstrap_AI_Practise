#pragma once

#include "IBehaviour.hpp"
#include <glm/vec2.hpp>
#include "Utility.h"
#include <functional>

/**
*	Behavioural state inheriting from IBehaviour interface class that handles moving in relation to a target.
*/
class Seek : public IBehaviour {
public:
	Seek(float a_innerRadius = 0.f, float a_outerRadius = 0.f) : m_innerRadius(a_innerRadius), m_outerRadius(a_outerRadius) {}
	virtual ~Seek();

	virtual void Update(GameObj* a_obj, float a_dt);
	virtual void Render(GameObj* a_obj, aie::Renderer2D* a_r2d);

	/**
	*	@brief Get position of the behaviour's target.
	*	@return 2d point in space of the target.
	*/
	const glm::vec2& GetTarget() { return m_targetPos; }
	float GetStrength() { return m_strength; }
	float GetInnerRadius() { return m_innerRadius; }
	float GetOuterRadius() { return m_outerRadius; }

	void SetTarget(glm::vec2& a_pos) { m_targetPos = a_pos; }
	void SetStrength(float a_str) { m_strength = a_str; }
	void SetInnerRadius(float a_rad) { m_innerRadius = a_rad; }
	void SetOuterRadius(float a_rad) { m_outerRadius = a_rad; }
	// Make parameters const so lambdas (lvalue functions) can be passed in
	void SetInnerRadiusEnter(const std::function<void()>& a_func) { m_innerRadEnter = a_func; }
	void SetOuterRadiusEnter(const std::function<void()>& a_func) { m_outerRadEnter = a_func; }
	void SetInnerRadiusExit(const std::function<void()>& a_func) { m_innerRadExit = a_func; }
	void SetOuterRadiusExit(const std::function<void()>& a_func) { m_outerRadExit = a_func; }


protected:
	glm::vec2 m_targetPos;			/*Position of target.*/
	
	float m_strength;				/*Strength of pursuing the target (negative lets it act like flee behaviour)*/
	float m_innerRadius;			/*Size of radius for reaching a target.*/
	float m_outerRadius;			/*Size of radius for flee range.*/

	// Initialise with empty lambda functions to avoid crashes
	std::function<void()> m_innerRadEnter	= []() {};
	std::function<void()> m_outerRadEnter	= []() {};
	std::function<void()> m_innerRadExit	= []() {};
	std::function<void()> m_outerRadExit	= []() {};

private:
	glm::vec2 m_lastPos;			/*Where game object was last frame (used for radius detection).*/
};