#include "Entities/Player.h"
#include "Behaviours/KeyboardController.h"
#include "Behaviours/Seek.h"
#include "Behaviours/FollowPath.h"
#include <Input.h>
#include "Utility.h"
#include "Path.h"
#include "PathFinder.h"
#include <Renderer2D.h>
#include <ResourcePack.h>
#include <glm/vec2.hpp>
#include <iostream>

Player::Player(glm::vec2 & a_pos, glm::vec2 & a_vel, float a_friction, IBehaviour * a_behaviour) :
	GameObj(a_pos, a_vel, a_friction, a_behaviour) // Call base constructor because the parameters pertain to the base class, not the inherited one.
{
	m_path = new Path;

#pragma region Behaviour initialisation
	// Seek
	m_seekBehaviour = new Seek;
	m_seekBehaviour->SetInnerRadiusEnter([this]() {
		SetBehaviour(m_controlBehaviour);
	});
	m_seekBehaviour->SetOuterRadiusExit([this]() {
		SetBehaviour(m_controlBehaviour);
	});
	m_seekBehaviour->IsOwned(true);				   // Belongs to game object, it is responsible for its deletion so that setting behaviour doesn't delete it.

	// Keyboard controller
	m_controlBehaviour = new KeyboardController;
	m_controlBehaviour->IsOwned(true);
	SetBehaviour(m_controlBehaviour);

	// Follow path
	m_followBehaviour = new FollowPath;
	m_followBehaviour->SetPath(m_path);
	m_followBehaviour->IsOwned(true);
#pragma endregion


}

Player::~Player()
{
	delete m_path;

	delete m_seekBehaviour;
	delete m_controlBehaviour;
	delete m_followBehaviour;
}

void Player::Update(float a_dt)
{
	// Call base update function
	GameObj::Update(a_dt);

#pragma region Behavioural mouse input
	aie::Input* input = aie::Input::getInstance();

	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);

	/// Left click
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		//// Follow path (free-form)
		if (input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL)) {
			// No need to set behaviour to follow path if its already doing so
			if (GetBehaviour() != m_followBehaviour) {
				SetBehaviour(m_followBehaviour);
			}

			// Add path segment
			m_path->PushPoint(glm::vec2(mouseX, mouseY));

			return;				// Avoid triggering multiple conditions
		}

		//// Follow path (conforms to grid)
		if (input->isKeyDown(aie::INPUT_KEY_LEFT_ALT)) {
			assert(m_pathFinder && "Attempted to path find with no path finder assigned to player.");
			
			// Make sure a node has been selected before assigning it
			auto nearNodes = m_pathFinder->GetGraph()->GetNearbyNodes(glm::vec2(mouseX, mouseY), NODE_RADIUS);
			if (!nearNodes.empty()) {
				// Selecting starting node
				if (!m_startNode) {
					m_startNode = nearNodes[0];
				}
				// OR Selecting goal node
				else if (!m_goalNode) {
					// All points selected
					m_goalNode = nearNodes[0];

					// Begin the calculations for finding the best path
					m_pathFinder->BeginPathFinding(m_startNode, m_goalNode, [this](Graph2D::Node* a_node) {
						return a_node == m_goalNode;
					});

					while (!m_pathFinder->IsSearchFinished()) {
						m_pathFinder->ContinuePathSearch();
					}

					// Path is calculated
					if (m_pathFinder->IsSearchFinished()) {
						// Take responsibility of previously owned path and clear memory before setting new one
						delete m_path;
						m_path = m_pathFinder->GetCurrentPath();
						m_followBehaviour->SetPath(m_path);

						// Set to follow behaviour if not already
						if (m_behaviour != m_followBehaviour) {
							SetBehaviour(m_followBehaviour);
						}
					}
				}
			}
		}

		//// Seek (only activates if there's no other button combinations)
		if (!input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT) && !input->isKeyDown(aie::INPUT_KEY_LEFT_ALT)) {
			m_seekBehaviour->SetTarget(glm::vec2(mouseX, mouseY));
			m_seekBehaviour->SetStrength(SEEK_STRENGTH);
			m_seekBehaviour->SetInnerRadius(SEEK_RADIUS);
			m_seekBehaviour->SetOuterRadius(0);

			SetBehaviour(m_seekBehaviour);
		}
	}

	/// Right click
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT)) {
		//// Flee (modified version of seek)
		m_seekBehaviour->SetTarget(glm::vec2(mouseX, mouseY));
		m_seekBehaviour->SetStrength(FLEE_STRENGTH);
		m_seekBehaviour->SetInnerRadius(0);
		m_seekBehaviour->SetOuterRadius(FLEE_RADIUS);

		SetBehaviour(m_seekBehaviour);
	}

	/// Clear path
	if (input->wasKeyPressed(aie::INPUT_KEY_C)) {
		// Reset start and goal nodes to allow for new selection
		m_startNode = nullptr;
		m_goalNode = nullptr;
		// Reset path
		m_path->Clear();

		// Relinquish control back to player
		SetBehaviour(m_controlBehaviour);
	}

//#ifdef _DEBUG
//	// Keep searching until goal is reached or all nodes have been searched
//	if (!m_pathFinder->IsSearchFinished() && input->wasKeyPressed(aie::INPUT_KEY_SPACE)) {
//		m_pathFinder->ContinuePathSearch();
//	}
//#endif
#pragma endregion
}

void Player::Render(aie::Renderer2D * a_r2d)
{
	// Call base render function
	GameObj::Render(a_r2d);

#ifdef _DEBUG
	if (m_startNode) {
		a_r2d->setRenderColour(0.f, 1.f, 0.f);
		a_r2d->drawCircle(m_startNode->GetData().x, m_startNode->GetData().y, NODE_RADIUS);
		a_r2d->setRenderColour(0xFFFFFFFF);
	}

	if (m_goalNode) {
		a_r2d->setRenderColour(1.f, 0.f, 0.f);
		a_r2d->drawCircle(m_goalNode->GetData().x, m_goalNode->GetData().y, NODE_RADIUS);
		a_r2d->setRenderColour(0xFFFFFFFF);

	}
#endif
}

void Player::SeekTarget(glm::vec2 & a_target)
{
	m_seekBehaviour->SetTarget(a_target);
	m_seekBehaviour->SetStrength(SEEK_STRENGTH);
	m_seekBehaviour->SetInnerRadius(SEEK_RADIUS);
	m_seekBehaviour->SetOuterRadius(0);

	SetBehaviour(m_seekBehaviour);
}
