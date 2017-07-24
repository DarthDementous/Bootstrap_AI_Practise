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
	IBehaviour() {}
	virtual ~IBehaviour() {}

	// Leave un-defined to make it an option for a derived class to inherit, not a pre-requisite.
	virtual void Update(GameObj* a_obj, float a_dt) {}
	virtual void Draw(GameObj* a_obj, aie::Renderer2D* a_r2d) {}				// Some behaviours may need to render things
protected:
private:
};