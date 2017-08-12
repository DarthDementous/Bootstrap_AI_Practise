#include "States/PatrolPath.h"
#include "Behaviours/FollowPath.h"
#include "PathFinder.h"

PatrolPath::PatrolPath(IAgent * a_host, PathFinder * a_pf) : m_pf(a_pf)
{
	m_followPath = new FollowPath(a_host);
	AddBehaviour("FOLLOW_PATH", m_followPath);
}

void PatrolPath::Startup()
{
	// Get random start and end node for path
	unsigned int graphSize = m_pf->GetGraph()->GetNodes()->size();

	m_startNode = m_pf->GetGraph()->GetNodeByID(rand() % graphSize);
	m_goalNode = m_pf->GetGraph()->GetNodeByID(rand() % graphSize);

	// Calculate path between random nodes and follow it
	m_pf->BeginPathFinding(m_startNode, {}, m_goalNode, HEURISTIC_FUNC);

	while (m_pf->ContinuePathSearch() == eSearchResult::SEARCHING) {}

	Path* path = m_pf->GetCurrentPath();

	// Only follow the path if it was found correctly
	if (path) {
		m_followPath->SetPath(m_pf->GetCurrentPath());
	}

	SetBehaviour("FOLLOW_PATH", false);
}

void PatrolPath::Update(float a_dt)
{
	AIState::Update(a_dt);

}

void PatrolPath::Draw(aie::Renderer2D * a_r2d)
{
	AIState::Draw(a_r2d);
}
