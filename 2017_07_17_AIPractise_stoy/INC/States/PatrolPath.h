#pragma once

#include "AIState.h"
#include "Graph/Graph2D.h"

class FollowPath;
class PathFinder;
class Circle;
class CollisionAvoidance;

/**
*	@brief Follow random path on grid looking for Agent.
*/
class PatrolPath : public AIState {
public:
	PatrolPath(IAgent* a_obj = nullptr, PathFinder* a_pf = nullptr, Graph2D::Node* a_startNode = nullptr);
	virtual ~PatrolPath();

	virtual void Startup();
	virtual void Update(float a_dt);
	virtual void Draw(aie::Renderer2D* a_r2d);
	virtual void Shutdown() {}

	/**
	*	@brief Check if given position intersects with search circle.
	*	@return true if found, false if not found.
	*/
	bool IsIntruderSpotted();

	/**
	*	@brief Update position to check if its in circle of vision.
	*	@param a_pos is the position to check.
	*	@return void.
	*/
	void SetCheckPos(const glm::vec2& a_pos) { m_checkPos = a_pos; }

	CollisionAvoidance* GetCollAvoid() { return m_collAvoid; }
protected:
	CollisionAvoidance* m_collAvoid = nullptr;

	PathFinder* m_pf;						/*Calculator of paths (A*). NOTE: Is not owned by state.*/
	FollowPath* m_followPath;				/*Behaviour for following a path.*/

	glm::vec2	m_checkPos;					/*Position to check for vision intersection with.*/

	IAgent*		m_host;						/*Need to hold onto host to get their velocity.*/
	Circle*		m_searchCircle;				/*Circle projected along object's heading (velocity) for detecting agent.*/

	Graph2D::Node* m_startNode = nullptr;
	// Randomly calculated destination node.
	Graph2D::Node* m_goalNode = nullptr;
private:
};