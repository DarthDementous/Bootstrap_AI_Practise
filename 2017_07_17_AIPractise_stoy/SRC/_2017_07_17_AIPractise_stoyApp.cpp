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
#include "Obstacles/Rect.h"
#include "Obstacles/Tri.h"
#include "Entities/NPC_Minion.h"
#include "Entities/NPC_Guard.h"
#include "Blackboard.h"
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
	
#pragma region Graph
	m_graph = new Graph2D;
	m_graph->LoadFromFile("./graph.txt");
	//// Add a grid of nodes to the graph (rows first from top left down)
	//for (size_t y = 0; y < GRAPH_HEIGHT; ++y) {
	//	for (size_t x = 0; x < GRAPH_WIDTH; ++x) {
	//		// Ensure the spacing is negative for the y because in Bootstrap it starts from 0.
	//		/* NOTE: Since we're multiplying with unsigned ints make sure its with something of higher precision (like a float)
	//		since otherwise the result of the expression will always be an unsigned int, leading to wrap around when made negative*/
	//		glm::vec2 pos((GRAPH_START_X + GRAPH_OFFSET_X) + (x * GRAPH_SPACING), (GRAPH_START_Y + GRAPH_OFFSET_Y) + (y * -GRAPH_SPACING));

	//		m_graph->AddNode(new Graph2D::Node(pos));
	//	}
	//}

	//// Add bidirected edges
	//for (auto node : *m_graph->GetNodes()) {
	//	// Connect current node to all nearby nodes specified by a radius
	//	auto nearbyNodes = m_graph->GetNearbyNodes(node->GetData(), SEARCH_RADIUS);

	//	for (auto nearNode : nearbyNodes) {
	//		// Don't connect node to itself
	//		if (node == nearNode) {
	//			continue;
	//		}
	//		// Add edge to home node with a weight of the distance from the home node
	//		m_graph->AddEdge(node, nearNode, true, glm::length(nearNode->GetData() - node->GetData()));
	//	}
	//}

#pragma endregion

	m_gr2d = new GraphRenderer2D(m_graph);

	m_pf = new PathFinder(m_graph);

#pragma region Obstacles
	m_obstacles.push_back(new Tri(glm::vec2(200.f, 200.f), glm::vec2(250.f, 250.f), glm::vec2(300.f, 200.f)));
	m_obstacles.push_back(new Tri(glm::vec2(300.f, 300.f), glm::vec2(350.f, 350.f), glm::vec2(400.f, 300.f)));
	m_obstacles.push_back(new Tri(glm::vec2(400.f, 400.f), glm::vec2(450.f, 450.f), glm::vec2(500.f, 400.f)));

	for (size_t i = 0; i < OBSTACLE_NUM; ++i) {
		m_obstacles.push_back(new Circle(glm::vec2(rand() % getWindowWidth(), rand() % getWindowHeight())));
		m_obstacles.push_back(new Rect(glm::vec2(rand() % getWindowWidth(), rand() % getWindowHeight())));
	}


#pragma endregion

#pragma region Player (must come after obstacles)
	m_player = new Player(glm::vec2(getWindowWidth() / 3, getWindowHeight() / 3));

	m_entities.push_back(m_player);
#pragma endregion

#pragma region NPCS (must come after obstacles)
	// Minions
	for (size_t i = 0; i < NPC_MINION_NUM; ++i) {
		glm::vec2 randPos = glm::vec2(rand() % getWindowWidth(), rand() % getWindowHeight());
		NPC_Minion* npc = new NPC_Minion(randPos);
		npc->SetObstacles(m_obstacles);

		m_entities.push_back(npc);
	}

	// Guards
	for (size_t i = 0; i < NPC_GUARD_NUM; ++i) {
		glm::vec2 randPos = glm::vec2(rand() % getWindowWidth(), rand() % getWindowHeight());
		Graph2D::Node* randStartNode = m_graph->GetNodeByID(rand() % m_graph->GetNodes()->size());	

		NPC_Guard* npc = new NPC_Guard(randPos, 1.f, m_pf, randStartNode);
		npc->SetObstacles(m_obstacles);

		m_entities.push_back(npc);
	}

#pragma endregion

	return true;
}

void _2017_07_17_AIPractise_stoyApp::shutdown() {
	Blackboard::Clear();

	for (auto obstacle : m_obstacles) {
		delete obstacle;
	}
	m_obstacles.clear();

	for (auto entity : m_entities) {
		delete entity;
	}
	m_entities.clear();

	delete m_gr2d;
	delete m_pf;
	delete m_graph;
	delete m_font;
	delete m_2dRenderer;

}

void _2017_07_17_AIPractise_stoyApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	Blackboard::Update(deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

#pragma region Graph (before player due to combined input conflict)
	m_graph->Update();
#pragma endregion

#pragma region Collision
	/// Boundary checks
	for (auto entity : m_entities) {
		const glm::vec2 pos = entity->GetPosition();

		// Left and right planes
		if (pos.x < PLAYER_RADIUS || pos.x > getWindowWidth() - PLAYER_RADIUS) {
			// Reflect the x axis 
			entity->SetVelocity(glm::vec2(-entity->GetVelocity().x * GLOBAL_RESTITUTION, entity->GetVelocity().y));
		}

		// Bottom and top window planes
		else if (pos.y < PLAYER_RADIUS || pos.y >getWindowHeight() - PLAYER_RADIUS) {
			// Reflect the y axis
			entity->SetVelocity(glm::vec2(entity->GetVelocity().x, -entity->GetVelocity().y * GLOBAL_RESTITUTION));
		}
	}
	

#pragma endregion

#pragma region Entities
	for (auto entity : m_entities) {
		entity->Update(deltaTime);
	}
#pragma endregion
}

void _2017_07_17_AIPractise_stoyApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_gr2d->Draw(m_2dRenderer);

	m_pf->Render(m_2dRenderer);
	
	// Obstacles
	for (auto obj : m_obstacles) {
		obj->Render(m_2dRenderer);
	}

#pragma region Entities
	for (auto entity : m_entities) {
		entity->Render(m_2dRenderer);
	}
#pragma endregion

	// output some text, uses the last used colour
	m_2dRenderer->drawText(ResourcePack::FontMap()["DEFAULT"].get(), "Press ESC to quit", 0, 0);

	// FPS
	char tmp[256];
	sprintf(tmp, "%i FPS", getFPS());
	m_2dRenderer->drawText(ResourcePack::FontMap()["DEFAULT"].get(), tmp, 50, (float)getWindowHeight() - 50);

	// done drawing sprites
	m_2dRenderer->end();
}