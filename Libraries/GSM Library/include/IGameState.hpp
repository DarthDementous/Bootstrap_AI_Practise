#pragma once
#include <iostream>

// Forward declarations
namespace aie {
	class Renderer2D;
}

class IGameState {
public:
	/*
	*	@brief	Base class that defines states of operation for an application.
	*	@param	a_r2d is the renderer pointer that we hold onto to draw states.
	*/
	IGameState(aie::Renderer2D* a_r2d = nullptr) : m_r2d(a_r2d) {
		Initialise();
	}
	virtual ~IGameState() {}						// Base classes that are inherited from must have virtual destructor so memory clean up happens for base class as well

	virtual void Initialise() = 0;
	virtual void Startup() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Shutdown() = 0;

	void SetUpdateActive(bool a_val) { updateIsActive = a_val; }
	void SetDrawActive(bool a_val) { drawIsActive = a_val; }

	bool IsUpdateActive() { return updateIsActive; }
	bool IsDrawActive() { return drawIsActive; }

protected:
	aie::Renderer2D* m_r2d = nullptr;

	bool updateIsActive = true;
	bool drawIsActive = true;
private:
};