#pragma once

#include <IGameState.hpp>

#pragma region Forward Declarations
class IAgent;
namespace aie {
	class Renderer2D;
}

#pragma endregion

/**
*	@brief Interface class all behaviours inherit from. Inherits from IGameState for compatability with state manager library.
*/
class IBehaviour : public IGameState {
public:
	IBehaviour(IAgent* a_obj = nullptr) : m_obj(a_obj) {}

	// Since functions are pure virtual, empty definitions must be supplied.
	virtual void Startup() {}
	virtual void Update(float deltaTime) {}
	virtual void Draw(aie::Renderer2D* a_r2d) {}
	virtual void Shutdown() {}

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

	/**
	*	@brief Normalize current scale by comparing it with total scale of behaviours.
	*	@return Normalized value (0-1.f) that can be used to scale steering force.
	*/
	float GetScaleFactor();
	float GetScale() { return m_scale; }

	void SetScale(float a_scale) { m_scale = a_scale; }

protected:
	IAgent* m_obj = nullptr;								/*Entity behaviour is assigned to.*/

	float m_scale = 1.f;									/*Scale of the steering forces (full by default)*/

	bool m_isOwned;
private:
};