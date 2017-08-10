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
#include "Obstacles/Circle.h"
#include "Entities/NPC.h"
#include <Behaviours/Seek.h>
#include <Behaviours/Wander.h>

_2017_07_17_AIPractise_stoyApp::_2017_07_17_AIPractise_stoyApp() {

}

_2017_07_17_AIPractise_stoyApp::~_2017_07_17_AIPractise_stoyApp() {

}

bool _2017_07_17_AIPractise_stoyApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	//m_font = new aie::Font("./font/consolas.ttf", 32);
	ResourcePack::FontMap()["DEFAULT"] = ResourceManager::loadResource<aie::Font>("./font/consolas.ttf", 32);
	ResourcePack::FontMap()["DBG"] = ResourceManager::loadResource<aie::Font>("./font/consolas.ttf", 12);

	ResourcePack::TextureMap()["TEST"] = ResourceManager::loadResource<aie::Texture>("./textures/JPG_test.jpg");

	std::vector<unsigned char> pixelVec;
	aie::Texture* a_tex = ResourcePack::TextureMap()["TEST"].get();

	for (int i = 0; i < (a_tex->getWidth() * a_tex->getHeight()); ++i) {
		pixelVec.push_back(a_tex->getPixels()[i]);
	}
	
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

#pragma region Obstacles
	m_obstacles.push_back(new Circle(glm::vec2(1000.f, 300.f), 20.f));

#pragma endregion

#pragma region Player (must come after obstacles)
	m_player = new Player(glm::vec2(getWindowWidth() / 2, getWindowHeight() / 2));
	m_player->SetVelocity(glm::vec2(10.f, 10.f));

	m_player->SetObstacles(m_obstacles);
#pragma endregion

#pragma region NPCS (must come after obstacles)
	for (size_t i = 0; i < NPC_NUM; ++i) {
		NPC* npc = new NPC(glm::vec2(i * 10, i * 10));
		Seek* seek = new Seek(npc);
		seek->SetInnerRadiusEnter([npc]() { npc->SetBehaviour("WANDER", true); });
		Wander* wander = new Wander(npc, PLAYER_WANDER_RADIUS, PLAYER_WANDER_DIST, PLAYER_JITTER);

		npc->AddBehaviour("SEEK", seek);
		npc->AddBehaviour("WANDER", wander);

		m_npcs.push_back(npc);
	}
#pragma endregion

	return true;
}

void _2017_07_17_AIPractise_stoyApp::shutdown() {
	for (auto obstacle : m_obstacles) {
		delete obstacle;
	}
	m_obstacles.clear();

	for (auto npc : m_npcs) {
		delete npc;
	}
	m_npcs.clear();

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

	// Left and right planes
	if (pos.x < PLAYER_RADIUS || pos.x > getWindowWidth() - PLAYER_RADIUS) {
		// Reflect the x axis 
		m_player->SetVelocity(glm::vec2(-m_player->GetVelocity().x * GLOBAL_RESTITUTION, m_player->GetVelocity().y));
	}

	// Bottom and top window planes
	else if (pos.y < PLAYER_RADIUS || pos.y >getWindowHeight() - PLAYER_RADIUS) {
		// Reflect the y axis
		m_player->SetVelocity(glm::vec2(m_player->GetVelocity().x, -m_player->GetVelocity().y * GLOBAL_RESTITUTION));
	}

	// Movement
	m_player->Update(deltaTime);
#pragma endregion

#pragma region NPCS
	for (auto npc : m_npcs) {
		npc->Update(deltaTime);
	}
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
	
	for (auto obj : m_obstacles) {
		obj->Render(m_2dRenderer);
	}

#pragma region NPCS
	for (auto npc : m_npcs) {
		npc->Render(m_2dRenderer);
	}
#pragma endregion

	// output some text, uses the last used colour
	m_2dRenderer->drawText(ResourcePack::FontMap()["DEFAULT"].get(), "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}