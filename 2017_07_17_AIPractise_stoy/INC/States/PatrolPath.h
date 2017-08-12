#pragma once

#include "AIState.h"
#include "Graph/Graph2D.h"

class FollowPath;
class PathFinder;

/**
*	@brief Generate a random path on the grid and follow it.
*/
class PatrolPath : public AIState {
public:
	PatrolPath(IAgent* a_obj = nullptr, PathFinder* a_pf = nullptr);
	virtual ~PatrolPath() {}

	virtual void Startup();
	virtual void Update(float a_dt);
	virtual void Draw(aie::Renderer2D* a_r2d);
	virtual void Shutdown() {}
protected:
	PathFinder* m_pf;						/*Calculator of paths (A*). NOTE: Is not owned by state.*/
	FollowPath* m_followPath;				/*Behaviour for following a path.*/

	// Randomly calculated or assigned start/end nodes
	Graph2D::Node* m_startNode;
	Graph2D::Node* m_goalNode;
private:
};