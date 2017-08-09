#include "Behaviours\Arrival.h"
#include <glm/gtx/norm.hpp>
#include "Entities\GameObj.h"
#include <Renderer2D.h>

Arrival::~Arrival()
{
}

void Arrival::Update(float deltaTime)
{
	float distanceToTarget = glm::length(m_targetPos - m_obj->GetPosition());		/*Vector between target and object.*/
	float arrivalStrength = m_strength;												/*Force towards target, modified if in slowing radius*/

																					// Object is within slowing radius
	if (distanceToTarget <= m_radius) {
		// Calcule current strength by scaling with factor of distance from target (1 (entered radius) - 0 (reached target))
		float scaleFactor = distanceToTarget / m_radius;

		// Zero out scale factor if at destination to avoid friction carrying object over goal, and floating point precision errors.
		if (scaleFactor < ARRIVAL_MIN) {
			scaleFactor = 0.f;
		}

		arrivalStrength *= scaleFactor;
	}

	// Calculate direction by creating vector between points and normalizing
	glm::vec2 wishDir = glm::normalize(m_targetPos - m_obj->GetPosition());

	// Replace velocity so there are no other forces acting on it during arrival process, and thus doesn't overshoot.
	m_obj->SetVelocity(wishDir * arrivalStrength);									// Use strength to scale vector before applying force to entity
}

void Arrival::Draw()
{
	// Mouse cursor
	m_r2d->drawBox(m_targetPos.x, m_targetPos.y, 4.f, 4.f);

	// Slowing radius
	m_r2d->setRenderColour(0.f, 0.f, 1.f, 0.25f);
	m_r2d->drawCircle(m_targetPos.x, m_targetPos.y, m_radius);

	m_r2d->setRenderColour(0xFFFFFFFF);
}

