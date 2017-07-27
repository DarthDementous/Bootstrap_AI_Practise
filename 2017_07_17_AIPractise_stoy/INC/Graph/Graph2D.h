#pragma once

#include "IGraph.hpp"
#include <glm/vec2.hpp>

/**
*	@brief Specialized inherited class of IGraph of type 2d vector
*	NOTE: Although base class is a template, inherited class does NOT need to be templated because the type is specified in the inheritance.
*/
class Graph2D : public IGraph<glm::vec2> {
public:
	/**
	*	@brief Modify graph according to user input.
	*	@return void.
	*/
	void Update();

	/**
	*	@brief Save current graph into a .txt file so it can be read with LoadFromFile()
	*	@param a_filename is the name of the .txt file. if not found, will be created.
	*/
	void SaveToFile(const char* a_filename);

	/**
	*	@brief Read in .txt file to construct graph.
	*	@param a_filename is the .txt file to load. if not found, assert will fail.
	*/
	void LoadFromFile(const char* a_filename);

	/**
	*	@brief Get all the nodes within a given range.
	*	@param a_pos is the position to search outwards from.
	*	@param a_radius is the extent of the search.
	*	@return vector of nearby nodes.
	*/
	std::vector<Node*> GetNearbyNodes(glm::vec2& a_pos, float a_radius);

protected:
private:
};