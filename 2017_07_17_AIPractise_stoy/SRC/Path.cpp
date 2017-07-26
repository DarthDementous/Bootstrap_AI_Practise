#include "Path.h"

void Path::PushPoint(const glm::vec2 & a_pt)
{
	m_pathPoints.push_back(a_pt);
}

void Path::PopPoint()
{
	// Check if necessary, std::vector might account for popping back on empty vectors already.
	if (!m_pathPoints.empty()) {
		m_pathPoints.pop_back();
	}
}
