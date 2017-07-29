#pragma once

#include <functional>
#include "Graph/Graph2D.h"
#include <list>
#include "Path.h"

#pragma region Forward Declarations
namespace aie {
	class Renderer2D;
}
#pragma endregion

/**
*	@brief Class that finds a path between two given nodes in a container.
*/
class PathFinder {
private:
	struct PathNode {
	public:
		PathNode(Graph2D::Node* a_node = nullptr, PathNode* a_parent = nullptr) : m_node(a_node), m_connectedParent(a_parent) {}

		/**
		*	@brief Get currently connected parent in determined path.
		*	@return Parent node this is connected to.
		*/
		PathNode* GetParent() { return m_connectedParent; }
		Graph2D::Node* GetNode() { return m_node; }

		/**
		*	@brief Set connection to parent node in path.
		*	@return void.
		*/
		void SetParent(PathNode* a_connectedParent) { m_connectedParent = a_connectedParent; }
		void SetNode(Graph2D::Node* a_node) { m_node = a_node; }
	public:
		float gScore = 0;						 /*Total cost (weight) to get to this node.*/
	private:
		Graph2D::Node* m_node		= nullptr;
		PathNode* m_connectedParent = nullptr;	 /*Stores which node its connected to in the path.*/
	};
public:
	PathFinder(Graph2D* a_graph) : m_graph(a_graph), m_pathFound(false) {
		m_currentPath = new Path;
	}
	~PathFinder();

	void Render(aie::Renderer2D* a_r2d);

	/**
	*	@brief Begin the process of determing the most efficient path from one given node to another. (Dijkstras)
	*	@param a_startNode is the node to begin searching out from.
	*	@param a_goalNode is the node that the path must end up at.
	*	@param a_goalTestFunc is the function to run to determine the requirements of successfully ending the search.
	*/
	void BeginPathFinding(Graph2D::Node* a_startNode, Graph2D::Node* a_goalNode, std::function<bool(Graph2D::Node*)> a_goalTestFunc);

	/**
	*	@brief Reset current path and try to find a more efficient one.
	*	@return void.
	*/
	void ContinuePathSearch();

	/**
	*	@brief Has an efficient path from the start node to the goal node been found yet?
	*	@return true = path to destination has been calculated, false = path to destination has not been calculated.
	*/
	bool IsSearchFinished() { return m_pathFound; }

	/**
	*	@brief Check whether 2d graph node is within list.
	*	@return nullptr if not in list, corresponding path node if found.
	*/
	PathNode* NodeInList(std::list<PathNode*> a_list, Graph2D::Node* a_node);

	Path* GetCurrentPath() { return m_currentPath; }
	Graph2D* GetGraph() { return m_graph; }

	void SetGraph(Graph2D* a_graph) { m_graph = a_graph; }
protected:
private:
	/**
	*	@brief Create path points from given node's parents, BEGINNING TO END
	*	@param a_goalNode is the path node to start backtracking from.
	*/
	void ConstructPath(PathNode* a_goalNode);
private:
	Graph2D* m_graph	   = nullptr;		/*Container of nodes to path find in.*/

	Path*	 m_currentPath = nullptr;		/*Current calculated path.*/

	bool	 m_pathFound;					/*Whether or not the best path has been found.*/

	std::function<bool(Graph2D::Node*)> m_goalReached;	/*Function determining the requirements for successfully making a path.*/

	std::list<PathNode*> m_open;			/*Nodes that still need to be processed.*/
	std::list<PathNode*> m_closed;			/*Nodes that have been processed.*/
};