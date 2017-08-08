#include "Behaviours/CollisionAvoidance.h"
#include <Renderer2D.h>
#include <Entities/GameObj.h>
#include <Obstacles/Circle.h>
#include <glm/gtx/norm.hpp>

CollisionAvoidance::~CollisionAvoidance()
{
	ClearRays();
}

void CollisionAvoidance::Update(GameObj * a_obj, float a_dt)
{
	/*
	1. Cast three rays out in the specified cone of vision
	2. Apply forces in direction of ray that didn't collide into anything, essentially moving around the object
	*/

	ClearRays();

	// Calculate angle from object velocity
	glm::vec2 objectDir = glm::normalize(a_obj->GetVelocity());
	m_velAngle = atan2f(objectDir.y, objectDir.x);

	// Calculate starting angle in FOV range (velocity angle - max variance) NOTE: velocity is in the middle of the fov range
	float raySpacing = m_fovAngle / (DEFAULT_COLLISION_RAYS - 1);		// Ray needs some space okay. (number of spaces is 1 less than the desired amount of rays)
	float currAngle = m_velAngle - (m_fovAngle / 2);

	/*m_rays.push_back(Util::Ray(a_obj->GetPosition(), glm::vec2(cosf(currAngle), sinf(currAngle)), m_losLength));*/

#pragma region Collision Detection
	for (int r = 0; r < DEFAULT_COLLISION_RAYS; ++r) {
		// Create ray (origin, direction, length)
		Util::Ray* ray = new Util::Ray(a_obj->GetPosition(), glm::vec2(cosf(currAngle), sinf(currAngle)), m_losLength);

		m_rays.push_back(ray);

		// Loop through collision objects and check for collision with ray
		for (auto collObj : a_obj->GetObstacles()) {
			glm::vec2 collPt = Util::FindCollisionPointOnRay(*ray, collObj->GetPos());

			/// Level 1 check: Possible collision, collision point isn't projected on ray but is at origin
			if (collPt != ray->origin) {
				/// Level 2 check: Definite collision, point intersects with circle
				auto circle = dynamic_cast<Circle*>(collObj);
				
				if (circle) {
					if (Util::PointVsCircle(collPt, circle) != eCollisionType::NONE) {
						ray->HasCollided = true;

						break;													// Ray has collided with something, no need to check rest of obstacles
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
		if (!ray->HasCollided) {
			m_avoidVec = ray->CalculateVector();
			
			break;																// Direction determined, no need to check other rays
		}
	}

	a_obj->ApplyForce(m_avoidVec);
#endif
}

void CollisionAvoidance::Render(GameObj * a_obj, aie::Renderer2D * a_r2d)
{
	a_r2d->setRenderColour(1.f, 0.f, 0.f);

	/*glm::vec2 anglePt = a_obj->GetPosition() + glm::vec2(cosf(m_velAngle), sinf(m_velAngle)) * 50.f;

	a_r2d->drawCircle(anglePt.x, anglePt.y, 5.f);
*/
	for (auto ray : m_rays) {
		glm::vec2 rayPt = a_obj->GetPosition() + ray->CalculateVector();

		a_r2d->drawLine(a_obj->GetPosition().x, a_obj->GetPosition().y, rayPt.x, rayPt.y, 1.f, 1.f);
	}

	a_r2d->setRenderColour(1.f, 0.f, 1.f);
	glm::vec2 avoidPt = a_obj->GetPosition() + m_avoidVec;
	a_r2d->drawLine(a_obj->GetPosition().x, a_obj->GetPosition().y, avoidPt.x, avoidPt.y, 2.f);

	a_r2d->setRenderColour(0xFFFFFFFF);
}

void CollisionAvoidance::ClearRays()
{
	for (auto ray : m_rays) {
		delete ray;
	}

	m_rays.clear();
}

