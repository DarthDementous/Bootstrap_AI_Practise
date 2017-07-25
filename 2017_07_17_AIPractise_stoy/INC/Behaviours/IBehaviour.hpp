#pragma once



#pragma region Forward Declarations
class GameObj;
namespace aie {
	class Renderer2D;
}

#pragma endregion

/**
*	@brief Interface class all behaviours inherit from.
*/
class IBehaviour {
public:
	IBehaviour(bool a_isOwned = true) : m_isOwned(a_isOwned) {}
	virtual ~IBehaviour() {}

	// Leave un-defined to make it an option for a derived class to inherit, not a pre-requisite.
	virtual void Update(GameObj* a_obj, float a_dt) {}
	virtual void Render(GameObj* a_obj, aie::Renderer2D* a_r2d) {}				// Some behaviours may need to render things

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
	bool m_isOwned;
private:
};