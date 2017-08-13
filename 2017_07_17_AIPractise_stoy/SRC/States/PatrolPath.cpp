#include "States/PatrolPath.h"
#include "Behaviours/FollowPath.h"
#include "Behaviours/CollisionAvoidance.h"
#include "PathFinder.h"
#include "Obstacles/Circle.h"
#include "Entities/IAgent.h"
#include "Utility.h"
#include <Renderer2D.h>

PatrolPath::PatrolPath(IAgent * a_host, PathFinder * a_pf, Graph2D::Node* a_startNode) : m_host(a_host), m_pf(a_pf), m_startNode(a_startNode)
{
	m_searchCircle = new Circle();

#pragma region Behaviour initialization
	m_followPath = new FollowPath(a_host);
	m_followPath->SetScale(50.f);
	AddBehaviour("FOLLOW_PATH", m_followPath);

	m_collAvoid = new CollisionAvoidance(a_host);
	m_collAvoid->SetScale(50.f);
	AddBehaviour("COLL_AVOID", m_collAvoid);
#pragma endregion
}

PatrolPath::~PatrolPath()
{
	delete m_searchCircle;
}

void PatrolPath::Startup()
{
	// Get destination for path
	unsigned int graphSize = m_pf->GetGraph()->GetNodes()->size();
	m_goalNode = m_pf->GetGraph()->GetNodeByID(rand() % graphSize);

	// If randomly generated node is the same as start node, keep generating until they're different
	while (m_goalNode == m_startNode) {
		m_goalNode = m_pf->GetGraph()->GetNodeByID(rand() % graphSize);
	}

	// Calculate path between random nodes and follow it
	m_pf->BeginPathFinding(m_startNode, {}, m_goalNode, HEURISTIC_FUNC);

	while (m_pf->ContinuePathSearch() == eSearchResult::SEARCHING) {}

	Path* path = m_pf->GetCurrentPath();

	// Only follow the path if one was found
	if (path) {
		m_followPath->SetPath(m_pf->GetCurrentPath());
	}

	SetBehaviour("FOLLOW_PATH", false);
	SetBehaviour("COLL_AVOID", false);
}

void PatrolPath::Update(float a_dt)
{
	AIState::Update(a_dt);

	// Update search circle position
	m_searchCircle->SetPos(m_host->GetPosition() + m_host->GetVelocity());
}

void PatrolPath::Draw(aie::Renderer2D * a_r2d)
{
	AIState::Draw(a_r2d);

	// Search circle
	a_r2d->setRenderColour(1.f, 1.f, 1.f, 0.4f);
	a_r2d->drawCircle(m_searchCircle->GetPos().x, m_searchCircle->GetPos().y, m_searchCircle->GetRadius());

	a_r2d->setRenderColour(0xFFFFFFFF);
}

bool PatrolPath::IsIntruderSpotted()
{
	if (Util::PointVsCircle(m_checkPos, m_searchCircle) != eCollisionType::NONE) {
		// Intruder spotted
		return true;
	} else {
		// Intruder not found
		return false;
	}
}
