#include "Behaviours/CollisionAvoidance.h"
#include <Renderer2D.h>
#include <Entities/IAgent.h>
#include "Obstacles/Circle.h"
#include "Obstacles/Rect.h"
#include "Obstacles/Tri.h"
#include <glm/gtx/norm.hpp>

CollisionAvoidance::~CollisionAvoidance()
{
	ClearRays();
}

void CollisionAvoidance::Update(float deltaTime)
{
	/*
	1. Cast rays out in the specified cone of vision
	2. Apply forces in direction of ray that didn't collide into anything, essentially moving around the object
	*/

	ClearRays();

	// If there is a velocity, calculate angle from object velocity
	if (m_obj->GetVelocity() != glm::vec2(0.f, 0.f)) {
		glm::vec2 objectDir = glm::normalize(m_obj->GetVelocity());
		m_velAngle = atan2f(objectDir.y, objectDir.x);
	}
	// No velocity, therefore angle of 0 (normalizing i.e. dividing by 0 gives nan errors)
	else {
		m_velAngle = 0.f;
	}


	// Calculate starting angle in FOV range (velocity angle - max variance) NOTE: velocity is in the middle of the fov range
	float raySpacing = m_fovAngle / (DEFAULT_COLLISION_RAYS - 1);		// Ray needs some space okay. (number of spaces is 1 less than the desired amount of rays)
	float currAngle = m_velAngle - (m_fovAngle / 2);

	bool collision = false;												// Has there been a collision this frame?

#pragma region Collision Detection
	for (int r = 0; r < DEFAULT_COLLISION_RAYS; ++r) {
		// Create ray (origin, direction, length)
		Util::Ray* ray = new Util::Ray(m_obj->GetPosition(), glm::vec2(cosf(currAngle), sinf(currAngle)), m_losLength);

		m_rays.push_back(ray);

		// Loop through collision objects and check for collision with ray
		for (auto collObj : m_obj->GetObstacles()) {
			glm::vec2 collPt = Util::FindCollisionPointOnRay(*ray, collObj->GetPos());

			/// Level 1 check: Possible collision, collision point is projected on ray and isn't at its origin
			if (collPt != ray->origin) {
				/// Level 2 check: Definite collision, point intersects
				auto circle = dynamic_cast<Circle*>(collObj);

				// Circle obstacle
				if (circle) {
					if (Util::PointVsCircle(collPt, circle) != eCollisionType::NONE) {
						ray->HasCollided = true;
						collision = true;

						break;									// Ray has collided with something, no need to check rest of obstacles
					}
				}

				auto rect = dynamic_cast<Rect*>(collObj);

				// Rectangle obstacle
				if (rect) {
					if (Util::PointVsRect(collPt, rect) != eCollisionType::NONE) {
						ray->HasCollided = true;
						collision = true;

						break;									// Ray has collided with something, no need to check rest of obstacles
					}
				}

				auto tri = dynamic_cast<Tri*>(collObj);
				
				// Triangle obstacle
				if (tri) {
					if (Util::PointVsTri(collPt, tri) != eCollisionType::NONE) {
						ray->HasCollided = true;
						collision = true;

						break;									// Ray has collided with something, no need to check rest of obstacles
					}
				}
			}
		}

		// Increment angle
		currAngle += raySpacing;
	}
#if 1

#pragma endregion
	
	// Find the first safe ray and apply force along it
	for (auto ray : m_rays) {
		if (!ray->HasCollided && collision == true) {					// Don't calculate avoid vector if there's no collision					
			m_avoidVec = ray->CalculateVector();

			break;														// Direction determined, no need to check other rays
		}
	}

	// Only apply force while one of the rays is colliding
	if (collision == true) {
		m_obj->ApplyForce(m_avoidVec * GetScaleFactor());
	}
#endif
}

void CollisionAvoidance::Draw(aie::Renderer2D* a_r2d)
{
#ifdef _DEBUG
	a_r2d->setRenderColour(1.f, 0.f, 0.f);

	/*glm::vec2 anglePt = m_obj->GetPosition() + glm::vec2(cosf(m_velAngle), sinf(m_velAngle)) * 50.f;

	m_r2d->drawCircle(anglePt.x, anglePt.y, 5.f);
	*/
	for (auto ray : m_rays) {
		glm::vec2 rayPt = m_obj->GetPosition() + ray->CalculateVector();

		a_r2d->drawLine(m_obj->GetPosition().x, m_obj->GetPosition().y, rayPt.x, rayPt.y, 1.f, 1.f);
	}

	a_r2d->setRenderColour(1.f, 0.f, 1.f);
	glm::vec2 avoidPt = m_obj->GetPosition() + m_avoidVec;
	a_r2d->drawLine(m_obj->GetPosition().x, m_obj->GetPosition().y, avoidPt.x, avoidPt.y, 2.f);

	a_r2d->setRenderColour(0xFFFFFFFF);
#endif
}

void CollisionAvoidance::ClearRays()
{
	// Clean dynamically allocated rays
	for (auto ray : m_rays) {
		delete ray;
	}

	// Reset vector of rays
	m_rays.clear();

	// Zero avoid vector so there's no force being applied in case of no collisions
	m_avoidVec = glm::vec2(0.f, 0.f);
}

