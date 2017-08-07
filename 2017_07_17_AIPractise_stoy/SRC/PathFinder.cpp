#include "PathFinder.h"
#include "Path.h"
#include <Renderer2D.h>
#include <MathLib_Utility.h>

PathFinder::~PathFinder()
{	
	// Delete memory for path nodes (open and closed list should never have the same pointers)
	for (auto openNode : m_open) {
		delete openNode;
	}
	m_open.clear();

	for (auto closeNode : m_closed) {
		delete closeNode;
	}
	m_closed.clear();
}

void PathFinder::BeginPathFinding(Graph2D::Node* a_startNode, std::function<bool(Graph2D::Node*)> a_goalTestFunc,	// Dijkstras
	Graph2D::Node* a_goalNode, std::function<int(Graph2D::Node*)> a_heuristicFunc)									// A*
{
	m_goalNode = a_goalNode;

	m_goalReachedFunc	= a_goalTestFunc;
	m_heuristicFunc		= a_heuristicFunc;

#pragma region Path initialization
	// Initialize path object
	m_currentPath = new Path;

	// Clear lists
	m_open.clear();
	m_closed.clear();

	// Begin by pushing start node onto open list
	PathNode* pathNode = new PathNode(a_startNode, nullptr);
	m_open.push_back(pathNode);
#pragma endregion
}

unsigned int PathFinder::ContinuePathSearch()
{
	// Still nodes left to process
	while (!m_open.empty()) {
		// Get current best path node (least gScore) from sorted open list and move into closed list 
		PathNode* bestPathNode = m_open.back();
		m_open.pop_back();
		m_closed.push_back(bestPathNode);

		// Check if best path node meets our requirements (NOTE: std::functions have implict conversions to bool to check if they've been assigned a lambda)
		/// Dijkstras
		if (m_goalReachedFunc) {
			if (m_goalReachedFunc(bestPathNode->GetNode())) { 
				ConstructPath(bestPathNode);

				return eSearchResult::FOUND; 
			}
		}

		///A*
		if (bestPathNode->GetNode() == m_goalNode) {
			ConstructPath(bestPathNode);

			return eSearchResult::FOUND;
		}

		// Loop through current node's edges and assign/update G score as path nodes
		auto edges = *bestPathNode->GetNode()->GetEdges();

		for (auto edge : edges) {
			Graph2D::Node* child = edge->m_to;

			// Calculate total cost for reaching this node (cost of reaching current node + cost of reaching current node's child + h score)
			float gScoreCurrent = bestPathNode->gScore + edge->GetWeight() + m_heuristicFunc(child);

			/// Determine G score for child path node
			PathNode* foundPathNode = NodeInList(m_closed, child);

			// Node has not been assigned a path node (not in open or closed list)
			if (!NodeInList(m_open, child) && !foundPathNode) {
				PathNode* pathNode = new PathNode(child, bestPathNode);
				pathNode->gScore = gScoreCurrent;

				// Add child to open list to be sorted by g score
				m_open.push_back(pathNode);
			}

			// Node is already a path node (in closed list)
			else if (foundPathNode) {
				// Cost via current path node is less than child's g score
				if (gScoreCurrent < foundPathNode->gScore) {
					// Set current path node as parent and update g score accordingly
					foundPathNode->SetParent(bestPathNode);
					foundPathNode->gScore = gScoreCurrent;
				}
			}
		}

		// Sort open list to determine next best path node (Nodes with better g score are at the END of the list)
		m_open.sort([this](PathNode* a_nodeA, PathNode* a_nodeB) { return a_nodeA->gScore > a_nodeB->gScore; });
	}

	// All nodes looked at, path not found.
	return eSearchResult::NOT_FOUND;
}

PathFinder::PathNode* PathFinder::NodeInList(std::list<PathNode*> a_list, Graph2D::Node * a_node)
{
	for (auto iter = a_list.begin(); iter != a_list.end(); ++iter) {
		// Found corresponding path node, return it
		if ((*iter)->GetNode() == a_node) {
			return (*iter);
		}
	}

	// No corresponding path node
	return nullptr;
}

void PathFinder::ConstructPath(PathNode * a_goalNode)
{
	// Prepare for constructing new path
	m_currentPath->Clear();

	// Add points to path and move to next parent until nullptr (at the starting node)
	PathNode* currentParent = a_goalNode;
	while (currentParent) {
		m_currentPath->PushPoint(currentParent->GetNode()->GetData());

		currentParent = currentParent->GetParent();
	}
	// Reverse path so it begins at starting node and ends at the goal node
	std::reverse(m_currentPath->GetPathPoints().begin(), m_currentPath->GetPathPoints().end());
}

void PathFinder::Render(aie::Renderer2D * a_r2d)
{
#ifdef _DEBUG
	a_r2d->setRenderColour(0x00f49bFF);
	for (auto path_node : m_open) {
		a_r2d->drawCircle(path_node->GetNode()->GetData().x, path_node->GetNode()->GetData().y, NODE_RADIUS / 2);
	}
	// Mint
	a_r2d->setRenderColour(0x7c29bcFF);
	for (auto path_node : m_closed) {
		a_r2d->drawCircle(path_node->GetNode()->GetData().x, path_node->GetNode()->GetData().y, NODE_RADIUS / 2);
	}
	a_r2d->setRenderColour(0xFFFFFFFF);
#endif
}
