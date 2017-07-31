#include "_2017_07_17_AIPractise_stoyApp.h"
#include <Texture.h>
#include <Font.h>
#include <Input.h>
#include "Entities/Player.h"
#include "Utility.h"
#include "Graph/GraphRenderer2D.h"
#include "Graph/Graph2D.h"
#include "Behaviours/KeyboardController.h"
#include <ResourceManager.hpp>
#include <ResourcePack.h>
#include <math.h>
#include <glm/gtx/norm.hpp>
#include "PathFinder.h"

_2017_07_17_AIPractise_stoyApp::_2017_07_17_AIPractise_stoyApp() {

}

_2017_07_17_AIPractise_stoyApp::~_2017_07_17_AIPractise_stoyApp() {

}

bool _2017_07_17_AIPractise_stoyApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	//m_font = new aie::Font("./font/consolas.ttf", 32);
	ResourcePack::FontMap()["DEFAULT"] = ResourceManager::loadResource<aie::Font>("./font/consolas.ttf", 32);
	ResourcePack::FontMap()["DBG"] = ResourceManager::loadResource<aie::Font>("./font/consolas.ttf", 12);


#pragma region Graph
	m_graph = new Graph2D;

	// Add a grid of nodes to the graph (rows first from top left down)
	for (size_t y = 0; y < GRAPH_HEIGHT; ++y) {
		for (size_t x = 0; x < GRAPH_WIDTH; ++x) {
			// Ensure the spacing is negative for the y because in Bootstrap it starts from 0.
			/* NOTE: Since we're multiplying with unsigned ints make sure its with something of higher precision (like a float)
			since otherwise the result of the expression will always be an unsigned int, leading to wrap around when made negative*/
			glm::vec2 pos((GRAPH_START_X + GRAPH_OFFSET_X) + (x * GRAPH_SPACING), (GRAPH_START_Y + GRAPH_OFFSET_Y) + (y * -GRAPH_SPACING));

			m_graph->AddNode(new Graph2D::Node(pos));
		}
	}

	// Add bidirected edges
	for (auto node : *m_graph->GetNodes()) {
		// Connect current node to all nearby nodes specified by a radius
		auto nearbyNodes = m_graph->GetNearbyNodes(node->GetData(), SEARCH_RADIUS);

		for (auto nearNode : nearbyNodes) {
			// Don't connect node to itself
			if (node == nearNode) {
				continue;
			}
			// Add edge to home node with a weight of the distance from the home node
			m_graph->AddEdge(node, nearNode, true, glm::length(nearNode->GetData() - node->GetData()));
		}
	}

#pragma endregion

	m_gr2d = new GraphRenderer2D(m_graph);

	m_pf = new PathFinder(m_graph);

#pragma region Player (must come after path finder)
	m_player = new Player(glm::vec2(getWindowWidth() / 2, getWindowHeight() / 2));
	m_player->SetBehaviour(new KeyboardController);
	m_player->SetPathFinder(m_pf);
#pragma endregion



	return true;
}

void _2017_07_17_AIPractise_stoyApp::shutdown() {
	delete m_player;
	delete m_gr2d;
	delete m_pf;
	delete m_graph;
	delete m_font;
	delete m_2dRenderer;

}

void _2017_07_17_AIPractise_stoyApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

#pragma region Graph (before player due to combined input conflict)
	m_graph->Update();
#pragma endregion

#pragma region Player
	/// Boundary checks
	const glm::vec2 pos = m_player->GetPosition();

	// Left plane
	if (pos.x < PLAYER_RADIUS || pos.x > getWindowWidth() - PLAYER_RADIUS) {
		// Reflect the x axis 
		m_player->SetVelocity(glm::vec2(-m_player->GetVelocity().x, m_player->GetVelocity().y));
	}

	// Bottom and top window planes
	else if (pos.y < PLAYER_RADIUS || pos.y >getWindowHeight() - PLAYER_RADIUS) {
		// Reflect the y axis
		m_player->SetVelocity(glm::vec2(m_player->GetVelocity().x, -m_player->GetVelocity().y));
	}

	// Movement
	m_player->Update(deltaTime);
#pragma endregion
}

void _2017_07_17_AIPractise_stoyApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_player->Render(m_2dRenderer);

	m_gr2d->Draw(m_2dRenderer);

	m_pf->Render(m_2dRenderer);
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(ResourcePack::FontMap()["DEFAULT"].get(), "Press ESC to quit", 0, 0);

//#ifdef _DEBUG
//	m_2dRenderer->setRenderColour(1.f, 0.f, 0.f, 0.1f);
//	for (auto node : *m_graph->GetNodes()) {
//		m_2dRenderer->drawCircle(node->GetData().x, node->GetData().y, SEARCH_RADIUS);
//	}
//	m_2dRenderer->setRenderColour(0xFFFFFFFF);
//#endif
	// done drawing sprites
	m_2dRenderer->end();
}