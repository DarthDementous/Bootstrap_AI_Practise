#include "_2017_07_17_AIPractise_stoyApp.h"
#include <Texture.h>
#include <Font.h>
#include <Input.h>
#include "GameObj.h"
#include "Utility.h"

_2017_07_17_AIPractise_stoyApp::_2017_07_17_AIPractise_stoyApp() {

}

_2017_07_17_AIPractise_stoyApp::~_2017_07_17_AIPractise_stoyApp() {

}

bool _2017_07_17_AIPractise_stoyApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_player = new GameObj(glm::vec2(getWindowWidth() / 2, getWindowHeight() / 2));

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
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}