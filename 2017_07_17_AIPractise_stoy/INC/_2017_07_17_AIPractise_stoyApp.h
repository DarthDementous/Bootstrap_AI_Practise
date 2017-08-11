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
class IAgent;

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

	std::vector<IAgent*>	m_entities;							/*Vector of all movable entities (for collision purposes)*/

	Graph2D*				m_graph		= nullptr;
	GraphRenderer2D*		m_gr2d		= nullptr;				/*2D Graph Renderer*/

	PathFinder*				m_pf		= nullptr;
	
	std::vector<IObstacle*>	m_obstacles;
};