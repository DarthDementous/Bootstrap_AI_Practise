#pragma once

#include "IObstacle.h"
#include <vector>

/**
*	@brief Triangle shaped obstacle.
*/
class Tri : public IObstacle {
public:
	Tri(glm::vec2 a_v1, glm::vec2 a_v2, glm::vec2 a_v3);
	Tri(glm::vec2 a_verts[3]);
	~Tri();

	virtual void Render(aie::Renderer2D* a_r2d);

	/**
	*	@brief Find the center of the triangle by calculating the average of the vertices.
	*	@return center point of triangle.
	*/
	glm::vec2 CalculateCenter();

	glm::vec2* GetVertices() { return m_verts; }
protected:
	glm::vec2 m_verts[3];			// Array of vertices
private:
};