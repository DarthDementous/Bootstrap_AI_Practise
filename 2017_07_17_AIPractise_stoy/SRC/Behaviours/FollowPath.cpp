#include "Behaviours\FollowPath.h"
#include "Path.h"
#include <Renderer2D.h>
#include "Utility.h"
#include <glm/gtx/normal.hpp>
#include <Entities/Player.h>

FollowPath::~FollowPath()
{
}

void FollowPath::Update(float deltaTime)
{
	// If there is a path to follow
	if (!m_path->GetPathPoints().empty()) {
		/* Wrap index back around in case it is out of range
		(e.g. index is 4 and size is 4, 4 % 4 = 0 || e.g. index is 2 and size is 8, 2 % 8 = 2 because 2 / 8 is 0, remainder 2) */
		m_currPathIndex = m_currPathIndex % m_path->GetPathPoints().size();

		glm::vec2 wishDir = m_path->At(m_currPathIndex) - m_obj->GetPosition();
		glm::vec2 normal = glm::normalize(wishDir);

		// Within certain distance of targeted point, target next node.
		if (glm::length(wishDir) < PATH_CHANGE_DIST + PLAYER_RADIUS) {
			++m_currPathIndex;
		}

		m_obj->ApplyForce(normal * SEEK_STRENGTH);
	}
}

void FollowPath::Draw()
{
#ifdef _DEBUG
	// Keep track of index because looping via iterator method
	size_t nodeCount = 0;

	/// Ensure that the path is rendered on top of everything (things that aren't default 0.f depth) in order to accurately see the path.
	for (auto iter = m_path->GetPathPoints().begin(); iter != m_path->GetPathPoints().end(); ++iter, ++nodeCount) {
		// Point
		m_r2d->setRenderColour(1.f, 1.f, 1.f, 0.25f);
		m_r2d->drawCircle(iter->x, iter->y, PATH_CHANGE_DIST);
		m_r2d->setRenderColour(0xFFFFFFFF);

		// Only draw a line if there is more than one node displayed
		if (nodeCount > 0) {
			glm::vec2 prevPt = *(iter - 1);

			// Make line gold to indicate the current edge being traversed
			m_currPathIndex = m_currPathIndex % m_path->GetPathPoints().size();		// Wrap around to avoid crashing while out of range
			if (*iter == m_path->At(m_currPathIndex)) {
				m_r2d->setRenderColour(0xf4d142FF);
			}
			m_r2d->drawLine(prevPt.x, prevPt.y, iter->x, iter->y, 2.f);

			m_r2d->setRenderColour(0xFFFFFFFF);
		}
	}
#endif
}


void FollowPath::SetPath(Path * m_path)
{
	// Change path and reset current path index
	m_path = m_path;
	m_currPathIndex = 0;
}
