#pragma once

#include "Application.h"
#include "Renderer2D.h"

class GameObj;

class _2017_07_17_AIPractise_stoyApp : public aie::Application {
public:

	_2017_07_17_AIPractise_stoyApp();
	virtual ~_2017_07_17_AIPractise_stoyApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	GameObj*			m_player = nullptr;
};