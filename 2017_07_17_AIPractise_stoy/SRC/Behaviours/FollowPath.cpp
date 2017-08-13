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
		// Reached end of path, reverse path so it loops
		if (m_currPathIndex == m_path->GetPathPoints().size() - 1) {
			std::reverse(m_path->GetPathPoints().begin(), m_path->GetPathPoints().end());

			// Reset index
			m_currPathIndex = 0;
		}

		glm::vec2 wishDir = m_path->At(m_currPathIndex) - m_obj->GetPosition();
		glm::vec2 normal = glm::normalize(wishDir);

		// Within certain distance of targeted point, target next node.
		if (glm::length(wishDir) < PATH_CHANGE_DIST + PLAYER_RADIUS) {
			++m_currPathIndex;
		}

		m_obj->ApplyForce(normal * SEEK_STRENGTH * GetScaleFactor());
	}
}

void FollowPath::Draw(aie::Renderer2D* a_r2d)
{
#ifdef _DEBUG
	// Keep track of index because looping via iterator method
	size_t nodeCount = 0;

	/// Ensure that the path is rendered on top of everything (things that aren't default 0.f depth) in order to accurately see the path.
	for (auto iter = m_path->GetPathPoints().begin(); iter != m_path->GetPathPoints().end(); ++iter, ++nodeCount) {
		// Point
		a_r2d->setRenderColour(1.f, 1.f, 1.f, 0.25f);
		a_r2d->drawCircle(iter->x, iter->y, PATH_CHANGE_DIST);
		a_r2d->setRenderColour(0xFFFFFFFF);

		// Only draw a line if there is more than one node displayed
		if (nodeCount > 0) {
			glm::vec2 prevPt = *(iter - 1);

			// Make line gold to indicate the current edge being traversed
			if (*iter == m_path->At(m_currPathIndex)) {
				a_r2d->setRenderColour(0xf4d142FF);
			}
			a_r2d->drawLine(prevPt.x, prevPt.y, iter->x, iter->y, 2.f);

			a_r2d->setRenderColour(0xFFFFFFFF);
		}
	}
#endif
}


void FollowPath::SetPath(Path * a_path)
{
	// Change path and reset current path index
	m_path = a_path;
	m_currPathIndex = 0;
}
