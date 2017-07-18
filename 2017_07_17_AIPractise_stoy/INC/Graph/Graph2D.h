#pragma once

#include "IGraph.hpp"
#include <glm/vec2.hpp>

/**
*	@brief Inherited class built from the blue-prints of IGraph of type Vector2.
*	NOTE: Although base class is a template, inherited class does NOT need to be templated because the type is specified in the inheritance.
*/
class Graph2D : public IGraph<glm::vec2> {
public:
	/**
	*	@brief Get all the nodes within a given range.
	*	@param a_pos is the position to search outwards from.
	*	@param a_radius is the extent of the search.
	*	@return void.
	*/
	std::vector<Node*>* GetNearbyNodes(glm::vec2& a_pos, float a_radius);
protected:
private:
};