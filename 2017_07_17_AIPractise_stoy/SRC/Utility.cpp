#include "Obstacles/Circle.h"
#include "Obstacles/Rect.h"
#include "Obstacles/Tri.h"

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

unsigned int Util::PointVsRect(glm::vec2 & a_pt, Rect * a_rect)
{
	// Intersection
	if (a_pt.x < a_rect->GetMin().x && a_pt.x > a_rect->GetMax().x && 
		a_pt.y > a_rect->GetMin().y && a_pt.y < a_rect->GetMax().y) {

		return eCollisionType::INTERSECTS;
	}

	// No collision
	else {
		return eCollisionType::NONE;
	}
}

///Credit to http://www.blackpawn.com/texts/pointinpoly/
unsigned int Util::PointVsTri(glm::vec2 & a_pt, Tri * a_tri)
{
	// 1. Check if point is left of BC by using A as a comparator
	if (SameSideOfLine(a_pt, a_tri->GetVertices()[0], a_tri->GetVertices()[1], a_tri->GetVertices()[2]) &&
	// 2. Check if point is above AC by using B as a comparator
		SameSideOfLine(a_pt, a_tri->GetVertices()[1], a_tri->GetVertices()[0], a_tri->GetVertices()[2]) &&
	// 3. Check if point is right of AB by using C as a comparator
		SameSideOfLine(a_pt, a_tri->GetVertices()[2], a_tri->GetVertices()[0], a_tri->GetVertices()[1])
		) {

		// All checks passed, must be inside triangle
		return eCollisionType::INTERSECTS;
	}
	else {
		// One or more checks failed, is not inside triangle
		return false;
	}
}

bool Util::SameSideOfLine(glm::vec2 & a_pt1, glm::vec2 & a_pt2, glm::vec2 & a_lineStart, glm::vec2 & a_lineEnd)
{
	glm::vec2 lineVec = a_lineEnd - a_lineStart;

	// Calculate 2d cross products between the line and the two points
	float cp1 = CrossProduct(lineVec, a_pt1 - a_lineStart);
	float cp2 = CrossProduct(lineVec, a_pt2 - a_lineStart);

	// Check if the dot-product between the scalar cross products are positive, if so they are on the same side
	if (glm::dot(cp1, cp2) >= 0) {
		return true;
	} else {
		return false;
	}
}


/// Credit to: http://www.allenchou.net/2013/07/cross-product-of-2d-vectors/
float Util::CrossProduct(glm::vec2 & a_vec1, glm::vec2 & a_vec2)
{
	// Calculate only the z-component
	return a_vec1.x * a_vec2.y - a_vec1.y * a_vec2.x;
}

glm::vec2 Util::LinearHalfPoint(glm::vec2 & a_start, glm::vec2 & a_head)
{
	// Create vector between points
	glm::vec2 vec = a_head - a_start;

	// Return mid-point
	return a_start + (vec / 2.f);
}
