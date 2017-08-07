#include "PathFinder.h"
#include "Path.h"
#include <Renderer2D.h>

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

void PathFinder::BeginPathFinding(Graph2D::Node* a_startNode, std::function<bool(Graph2D::Node*)> a_goalTestFunc,		// Dijkstras
	Graph2D::Node* a_goalNode, std::function<int()> a_heuristicFunc)
{
	m_goalReachedFunc	= a_goalTestFunc;
	m_heuristicFunc		= a_heuristicFunc;

#pragma region Path initialization
	// Replace old path
	delete m_currentPath;
	m_currentPath = new Path;

	// Clear lists
	m_open.clear();
	m_closed.clear();

	// Begin by pushing start node onto open list
	PathNode* pathNode = new PathNode(a_startNode, nullptr);
	m_open.push_back(pathNode);
#pragma endregion
}

void PathFinder::ContinuePathSearch()
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

		}
	}

	if (!m_pathFound) {


		// Requirements met for successful path
		if (m_goalReached(bestPathNode->GetNode())) {
			// Create path by backtracking from goal node
			ConstructPath(bestPathNode);
			
			m_pathFound = true;
			return;
		}

		auto edges = bestPathNode->GetNode()->GetEdges();

		// Loop through all of the current best node's children and process them
		for (size_t i = 0; i < edges->size(); ++i) {
			Graph2D::Node* child = edges->at(i)->m_to;

			float cost = edges->at(i)->GetWeight();
			float gScoreCurrent = bestPathNode->gScore + cost;

			PathNode* nodeInList = NodeInList(m_open, child);
			// Child is not waiting to be processed in open list
			if (!nodeInList) {
				// Check if child is in closed list
				nodeInList = NodeInList(m_closed, child);
			}
			// Child has not been assigned a corresponding path node
			if (!nodeInList) {
				// Create path node with child, calculate its G score and push it to the open list
				PathNode* pathNode = new PathNode(child, bestPathNode);
				pathNode->gScore = gScoreCurrent;

				m_open.push_back(pathNode);
			}
			// Node has already been processed into closed list but could be put in a more efficient position
			else {
				/* Total cost to get to that node is greater than getting there from current best node, 
				save new path by making best node the parent and updating to new and better G score*/
				if (nodeInList->gScore > gScoreCurrent) {
					nodeInList->SetParent(bestPathNode);
					nodeInList->gScore = gScoreCurrent;
				}
			}
		}
		// Sort open list so less costly path nodes to reach are at the END of the list.
		m_open.sort([this](PathNode* a_nodeA, PathNode* a_nodeB) { return a_nodeA->gScore > a_nodeB->gScore; });

	}
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
