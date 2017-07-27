#include "Behaviours\FollowPath.h"
#include "Path.h"
#include <Renderer2D.h>
#include "Utility.h"
#include <glm/gtx/normal.hpp>
#include <Entities/Player.h>

FollowPath::~FollowPath()
{
}

void FollowPath::Update(GameObj * a_obj, float a_dt)
{
	// If there is a path to follow
	if (!m_path->GetPathPoints().empty()) {
		/* Wrap index back around in case it is out of range 
		(e.g. index is 4 and size is 4, 4 % 4 = 0 || e.g. index is 2 and size is 8, 2 % 8 = 2 because 2 / 8 is 0, remainder 2) */
		m_currPathIndex = m_currPathIndex % m_path->GetPathPoints().size();

		glm::vec2 wishDir = m_path->At(m_currPathIndex) - a_obj->GetPosition();
		glm::vec2 normal  = glm::normalize(wishDir);

		// Within certain distance of targeted point, target next node.
		if (glm::length(wishDir) < PATH_DIST_CHANGE + PLAYER_RADIUS) {
			++m_currPathIndex;
		}

		a_obj->ApplyForce(normal * SEEK_STRENGTH);
	}
}

void FollowPath::Render(GameObj * a_obj, aie::Renderer2D * a_r2d)
{
#ifdef _DEBUG
	// Keep track of index because looping via iterator method
	size_t nodeCount = 0;

	for (auto iter = m_path->GetPathPoints().begin(); iter != m_path->GetPathPoints().end(); ++iter, ++nodeCount) {
		// Point
		a_r2d->setRenderColour(1.f, 1.f, 1.f, 0.25);
		a_r2d->drawCircle(iter->x, iter->y, PATH_DIST_CHANGE);
		a_r2d->setRenderColour(0xFFFFFFFF);

		// Only draw a line if there is more than one node displayed
		if (nodeCount > 0) {
			glm::vec2 prevPt = *(iter - 1);

			// Make line gold to indicate the current edge being traversed
			if (*iter == m_path->At(m_currPathIndex)) {
				a_r2d->setRenderColour(0xf4d142FF);
			}
			a_r2d->drawLine(prevPt.x, prevPt.y, iter->x, iter->y);

			a_r2d->setRenderColour(0xFFFFFFFF);
		}
	}
#endif
}
