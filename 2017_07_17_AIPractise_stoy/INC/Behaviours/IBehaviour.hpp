#pragma once

#include <IGameState.hpp>

#pragma region Forward Declarations
class GameObj;
namespace aie {
	class Renderer2D;
}

#pragma endregion

/**
*	@brief Interface class all behaviours inherit from. Inherits from IGameState for compatability with state manager library.
*/
class IBehaviour : public IGameState {
public:
	IBehaviour(GameObj* a_obj = nullptr) : m_obj(a_obj) {}
	/**
	*	@brief Returns whether or not behaviour is assigned to a game object.
	*	@return is it owned (true), or isn't it (false)
	*/
	bool IsOwned() { return m_isOwned; }

	/**
	*	@brief Change the status of whether the behaviour is assigned to a game object or not.
	*	@return void.
	*/
	void IsOwned(bool a_isOwned) { m_isOwned = a_isOwned; }

protected:
	aie::Renderer2D* m_renderer = nullptr;					/*Pointer to renderer for drawing behaviours.*/

	GameObj* m_obj = nullptr;								/*Entity behaviour is assigned to.*/

	bool m_isOwned;
private:
};