#pragma once

#include "Entities/GameObj.h"
#include <GameStateManager.h>

class GameStateManager;

/**
*	@brief Interface base class for entities that use behaviours.
*/
class IAgent : public GameObj {
public:
	IAgent();
	virtual ~IAgent();
protected:
	GameStateManager* m_behaviourManager = nullptr;			/*Handles update/rendering/changing etc. of behaviours.*/
private:
};