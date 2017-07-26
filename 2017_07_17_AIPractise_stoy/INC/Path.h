#pragma once

#include <glm/vec2.hpp>
#include <vector>

class Path {
public:
	Path() {}
	~Path() {}

	/**
	*	@brief Add path segment to end of the path.
	*	@param a_pt is the point to add.
	*	@return void.
	*/
	void PushPoint(const glm::vec2& a_pt);
	
	/**
	*	@brief Remove path segment at the end of the path.
	*	@return void.
	*/
	void PopPoint();

	/**
	*	@brief Clear all points on current path.
	*	@return void.
	*/
	void Clear();

	/**
	*	@brief Get point at given index.
	*	@return 2D point from specified index.
	*/
	glm::vec2& At(size_t a_index) { return m_pathPoints[a_index]; }

	std::vector<glm::vec2>& GetPathPoints() { return m_pathPoints; }
protected:
	std::vector<glm::vec2> m_pathPoints;					/*Container of all points that make up the current path.*/
private:
};