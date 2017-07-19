#include "_2017_07_17_AIPractise_stoyApp.h"
#include <Texture.h>
#include <Font.h>
#include <Input.h>
#include "GameObj.h"
#include "Utility.h"
#include "Graph/GraphRenderer2D.h"
#include "Graph/Graph2D.h"

_2017_07_17_AIPractise_stoyApp::_2017_07_17_AIPractise_stoyApp() {

}

_2017_07_17_AIPractise_stoyApp::~_2017_07_17_AIPractise_stoyApp() {

}

bool _2017_07_17_AIPractise_stoyApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_player = new GameObj(glm::vec2(getWindowWidth() / 2, getWindowHeight() / 2));

#pragma region Graph
	m_graph = new Graph2D;

	// Add a grid of nodes to the graph
	for (auto y = 0; y < GRAPH_HEIGHT; ++y) {
		for (auto x = 0; x < GRAPH_WIDTH; ++x) {
			// Ensure the spacing is negative for the y because in Bootstrap it starts from 0.
			glm::vec2 pos((GRAPH_START_X + GRAPH_OFFSET_X) + (x * GRAPH_SPACING), (GRAPH_START_Y + GRAPH_OFFSET_Y) + -(y * GRAPH_SPACING));
			
			Graph2D::Node* newNode = new Graph2D::Node(pos);
			m_graph->AddNode(newNode);
		}
	}

	// Add bidirected edges
	Graph2D::Node* startNode = SEARCH_NODE;

	for (auto node : m_graph->GetNearbyNodes(startNode->GetData(), SEARCH_RADIUS)) {
		// Don't connect the node to itself
		if (startNode != node) {
			m_graph->AddEdge(startNode, node, true);
		}
	}

	// One directed edge
	m_graph->AddEdge(startNode, m_graph->GetNodes()->back(), false);
	
	//for (auto iter = m_graph->GetNodes()->begin(); iter != m_graph->GetNodes()->end(); ++iter) {
	//	auto nextIter = iter + 1;
	//	
	//	// Make sure the next node isn't garbage before we access it
	//	if (nextIter != m_graph->GetNodes()->end()) {
	//		m_graph->AddEdge(*iter, *(nextIter), true);
	//	}
	//}

#pragma endregion
	m_gr2d = new GraphRenderer2D(m_graph);

	return true;
}

void _2017_07_17_AIPractise_stoyApp::shutdown() {
	delete m_player;
	delete m_font;
	delete m_2dRenderer;
}

void _2017_07_17_AIPractise_stoyApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

#pragma region Player
	// Input
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		m_player->ApplyForce(glm::vec2(1000, 0));
	}

	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		m_player->ApplyForce(glm::vec2(-1000, 0));
	}

	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		m_player->ApplyForce(glm::vec2(0, 1000));
	}

	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		m_player->ApplyForce(glm::vec2(0, -1000));
	}

	// Boundary checks
	const glm::vec2 pos = m_player->GetPosition();

	// If outside bounds, reflect velocity and clear acceleration
	if (pos.x < PLAYER_RADIUS * 2 || pos.x > getWindowWidth() - PLAYER_RADIUS * 2 || pos.y < PLAYER_RADIUS * 2 || pos.y > getWindowHeight() - PLAYER_RADIUS * 2) { 
		m_player->SetVelocity(-m_player->GetVelocity());
		m_player->SetAcceleration(glm::vec2(0, 0));
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

#ifdef _DEBUG
	m_2dRenderer->setRenderColour(1, 0, 0, 0.5);
	m_2dRenderer->drawCircle(SEARCH_NODE->GetData().x, SEARCH_NODE->GetData().y, SEARCH_RADIUS);
	m_2dRenderer->setRenderColour(0, 0, 0, 0);
#endif
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}