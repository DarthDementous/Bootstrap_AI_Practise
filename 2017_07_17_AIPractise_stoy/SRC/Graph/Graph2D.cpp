#include "Graph\Graph2D.h"
#include <glm/gtx/norm.hpp>

std::vector<Graph2D::Node*> Graph2D::GetNearbyNodes(glm::vec2& a_pos, float a_radius)
{
	std::vector<Graph2D::Node*> nearbyNodes;

	// Loop through all nodes and add those within the given range
	for (auto node : *m_nodes) {
		// Find magnitude of vector between circle origins. glm::length(v) INSTEAD of v.length(), the latter gives the dimension instead.
		auto distance = glm::length(node->GetData() - a_pos);

		if (distance < node->GetRadius() + a_radius) {
			nearbyNodes.push_back(node);
		}
	}

	return nearbyNodes;
}
