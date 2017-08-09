#include "Entities/IAgent.h"
#include <GameStateManager.h>s

IAgent::IAgent()
{
	m_behaviourManager = new GameStateManager;
}

IAgent::~IAgent()
{
	delete m_behaviourManager;
}

void GameObj::SetObstacles(std::vector<IObstacle*> a_obs)
{
	for (auto obstacle : m_obstacles) {
		delete obstacle;				/*Clear dynamically allocated memory.*/
	}

	m_obstacles = a_obs;
}

