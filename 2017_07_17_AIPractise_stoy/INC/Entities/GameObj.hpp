#pragma once

#include <glm/vec2.hpp>
#include <iostream>

#pragma region Forward Declarations
namespace aie {
	class Renderer2D;
}
#pragma endregion

/**
*	@brief Base class for game entities.
*/
class GameObj {
public:
	GameObj(const glm::vec2& a_pos = glm::vec2(0.f, 0.f)) : m_pos(a_pos) {}

	virtual ~GameObj() {}

	virtual void Update(float a_dt) = 0;
	virtual void Render(aie::Renderer2D* a_r2d) = 0;

	// Have getters return const because we don't want the referenced values to be modified outside of the setters.
	const glm::vec2& GetPosition() { return m_pos; }

	void SetPosition(const glm::vec2& a_pos) { m_pos = a_pos; }

protected:
	glm::vec2 m_pos;						/*Object's current position.*/
private:
};