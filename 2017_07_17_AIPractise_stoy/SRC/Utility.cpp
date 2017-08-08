#include "Obstacles/Circle.h"

unsigned int Util::PointVsCircle(glm::vec2 & a_pt, Circle * a_circle)
{
	float distance = Math_Util::Magnitude(a_circle->GetPos() - a_pt);		/*Length of vector between point and circle.*/

	// Intersection
	if (distance < a_circle->GetRadius()) {
		return eCollisionType::INTERSECTS;
	}

	// Adjust (point rests on the circumference)
	else if (distance == a_circle->GetRadius()) {
		return eCollisionType::ADJUST;
	}

	// No collision
	else {
		return eCollisionType::NONE;
	}
}
