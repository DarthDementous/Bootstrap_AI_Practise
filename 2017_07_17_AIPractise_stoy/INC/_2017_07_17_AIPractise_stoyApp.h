#pragma once

#include <Application.h>
#include <Renderer2D.h>
#include <vector>

#pragma region Forward Declarations
class Player;
class GraphRenderer2D;
class Graph2D;
class PathFinder;
class IObstacle;
class NPC;

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

	aie::Renderer2D*		m_2dRenderer;
	aie::Font*				m_font = nullptr;

	Player*					m_player	= nullptr;

	std::vector<NPC*>		m_npcs;

	Graph2D*				m_graph		= nullptr;
	GraphRenderer2D*		m_gr2d		= nullptr;				/*2D Graph Renderer*/

	PathFinder*				m_pf		= nullptr;
	
	std::vector<IObstacle*>	m_obstacles;
};