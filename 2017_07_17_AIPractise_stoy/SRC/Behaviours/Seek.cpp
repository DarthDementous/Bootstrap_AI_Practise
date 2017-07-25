#include "Behaviours/Seek.h"
#include <Renderer2D.h>
#include "Entities/GameObj.h"
#include <glm/gtx/norm.hpp>

Seek::~Seek()
{
}

void Seek::Update(GameObj * a_obj, float a_dt)
{
#pragma region Radius checks
	float lastTargetDistance	= glm::length(m_targetPos - m_lastPos);				/*How far away we were from target last frame.*/
	float distanceToTarget		= glm::length(m_targetPos - a_obj->GetPosition());	/*How far away we are from target this frame.*/

	// Entered inner radius
	if (lastTargetDistance > m_innerRadius && distanceToTarget <= m_innerRadius) {
		m_innerRadEnter();
	}
	else if (lastTargetDistance <= m_innerRadius && distanceToTarget > m_innerRadius) {
		// Exited inner radius
		m_innerRadExit();
	}

	// Entered outer radius
	if (lastTargetDistance > m_outerRadius && distanceToTarget <= m_outerRadius) {
		m_outerRadEnter();
	}
	else if (lastTargetDistance <= m_outerRadius && distanceToTarget > m_outerRadius) {
		// Exited outer radius
		m_outerRadExit();
	}
#pragma endregion

#pragma region Movement
	// Calculate direction by creating vector between points and normalizing
	glm::vec2 wishDir = glm::normalize(m_targetPos - a_obj->GetPosition());

	a_obj->ApplyForce(wishDir * m_strength);					// Use strength to scale vector before applying force to entity
#pragma endregion
	
	// Update last frame position
	m_lastPos = a_obj->GetPosition();
}

void Seek::Render(GameObj * a_obj, aie::Renderer2D * a_r2d)
{
	// Cursor
	a_r2d->drawBox(m_targetPos.x, m_targetPos.y, 4, 4);
	// Radii
	a_r2d->setRenderColour(1.0, 1.0, 1.0, 0.75);
	a_r2d->drawCircle(m_targetPos.x, m_targetPos.y, m_innerRadius);
	a_r2d->setRenderColour(1.0, 1.0, 1.0, 0.25);
	a_r2d->drawCircle(m_targetPos.x, m_targetPos.y, m_outerRadius);

	a_r2d->setRenderColour(0xFFFFFFFF);
}
