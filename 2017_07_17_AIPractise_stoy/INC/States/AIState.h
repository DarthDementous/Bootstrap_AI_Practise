#pragma once

#include <IGameState.hpp>

class IAgent;
class IBehaviour;
class GameStateManager;

/**
*	@brief Class that manipulates steering behaviours to produce certain functionality for an agent.
*/
class AIState : public IGameState {
public:
	AIState(IAgent* a_host = nullptr);
	virtual ~AIState();

	void SetUtility(float a_util) { m_utility = a_util; }
	
	float GetUtility() { return m_utility; }

	virtual void Startup() {}
	virtual void Update(float a_dt);
	virtual void Draw(aie::Renderer2D* a_r2d);
	virtual void Shutdown() {}

	GameStateManager* GetBehaviourManager() { return m_behaviourManager; }
protected:
	/**
	*	@brief Set behaviour from list of given behaviours by key.
	*	@param a_name is the name of the behaviour to set. (must already be added)
	*	@param a_replace determines whether it pops the current active state before setting (true) or adds to active behaviours (false).
	*/
	void SetBehaviour(const char* a_name, bool a_replace);
	/**
	*	@brief Set behaviour from list of given behaviours by value.
	*	@param a_beh is the pointer to the behaviour. (must already be added)
	*	@param a_replace determines whether to pop the current active state before setting (true) or just add on top to active behaviours (false)
	*/
	void SetBehaviour(IBehaviour* a_beh, bool a_replace);

	/**
	*	@brief Add behaviour to list of possible behaviours.
	*	@param a_name is the key to identify the behaviour with.
	*	@param a_beh is the behaviour to push to the behaviour manager.
	*/
	void AddBehaviour(const char* a_name, IGameState* a_beh);
protected:
	float m_utility = 0.f;			/*Arbitrary value assigned to determine best possible state (0 by default).*/

	GameStateManager* m_behaviourManager = nullptr;
private:

};