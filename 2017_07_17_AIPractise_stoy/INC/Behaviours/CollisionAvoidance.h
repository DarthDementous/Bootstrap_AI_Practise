#pragma once

#include "IBehaviour.h"
#include <vector>
#include <glm/vec2.hpp>
#include "Utility.h"
#include <MathLib_Utility.h>

/**
*	@brief Behaviour that handles moving around obstacles.
*/
class CollisionAvoidance : public IBehaviour {
public:
	CollisionAvoidance(IAgent* a_obj = nullptr, float a_fovAngle = Math_Util::degToRad(FOV_RANGE), float a_losLength = LOS_LENGTH) : 
		IBehaviour(a_obj), m_fovAngle(a_fovAngle), m_losLength(a_losLength) {}
	~CollisionAvoidance();

	virtual void Startup() {}
	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D* a_r2d);
	virtual void Shutdown() {}

	void ClearRays();
protected:
	float m_velAngle;				/*Angle of the object's velocity.*/
	float m_fovAngle;				/*Range of vision to cast out collision detection rays.*/
	float m_losLength;				/*Maximum length of ray cast (Line of Sight)*/

	glm::vec2 m_avoidVec;			/*Vector of direction to move in to avoid object*/

	std::vector<Util::Ray*>	m_rays;	/*Rays that have not collided with an obstacle. DEBUGGING: Store LOS rays to draw them.*/
private:
};