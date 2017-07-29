#pragma once

#include <Application.h>
#include <Renderer2D.h>


#pragma region Forward Declarations
class Player;
class GraphRenderer2D;
class Graph2D;
class PathFinder;

#pragma endregion

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
	aie::Font*			m_font = nullptr;

	Player*				m_player	= nullptr;

	Graph2D*			m_graph		= nullptr;
	GraphRenderer2D*	m_gr2d		= nullptr;				/*2D Graph Renderer*/

	PathFinder*			m_pf		= nullptr;
};