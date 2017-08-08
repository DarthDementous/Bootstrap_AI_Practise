#pragma once

#include <glm/vec2.hpp>
#include "Utility.h"


#pragma region Forward Declarations
class IBehaviour;
namespace aie {
	class Renderer2D;
}

class IObstacle;
#pragma endregion

/**
*	@brief Base class for game entities. Is able to update and render.
*/
class GameObj {
public:
	GameObj(glm::vec2& a_pos = glm::vec2(0, 0), glm::vec2& a_vel = glm::vec2(0, 0), float a_friction = PLAYER_FRICTION, IBehaviour* a_behaviour = nullptr);

	virtual ~GameObj();

	virtual void Update(float a_dt);
	virtual void Render(aie::Renderer2D* a_r2d);

	/**
	*	@brief Modify acceleration of the object by setting an active force.
	*	@param a_force is the vector of force to ADD onto the acceleration.
	*	@return void.
	*/
	void ApplyForce(const glm::vec2& a_force) { m_accel += a_force; }

	/**
	*	@brief Calculates trajectory for update frame based on velocity, acceleration and friction.
	*	@param a_dt is the time between frames for normalising calculations.
	*/
	void MovementPhysics(float a_dt);



	// Have getters return const because we don't want the referenced values to be modified outside of the setters.
	const glm::vec2& GetPosition() { return m_pos; }
	const glm::vec2& GetVelocity() { return m_vel; }
	const float GetFriction() { return m_friction; }
	const float GetRotation() { return m_rot; }
	const IBehaviour* GetBehaviour() { return m_behaviour; }
	const std::vector<IObstacle*>& GetObstacles() { return m_obstacles; }

	void SetPosition(const glm::vec2& a_pos) { m_pos = a_pos; }
	void SetVelocity(const glm::vec2& a_vel) { m_vel = a_vel; }
	void SetFriction(const float a_friction) { m_friction = a_friction; }
	void SetRotation(const float a_rot) { m_rot = a_rot; }
	void SetAcceleration(const glm::vec2& a_accel) { m_accel = a_accel; }
	void SetBehaviour(IBehaviour* a_behaviour);
	
	/**
	*	@brief Change and clear currently held vector of obstacles.
	*	@param a_obs is the vector of obstacles to assign.
	*/
	void SetObstacles(std::vector<IObstacle*> a_obs);
protected:
	glm::vec2 m_pos;						/*Object's current position.*/
	glm::vec2 m_vel;						/*What to move the object by each frame.*/
	glm::vec2 m_accel;						/*Rate at which the object moves each frame.*/

	float	  m_friction;					/*Rate at which to minimize velocity.*/
	float	  m_rot;						/*Rotation.*/

	IBehaviour* m_behaviour;				/*Current active behaviour.*/

	std::vector<IObstacle*> m_obstacles;	/*Vector of obstacles to avoid. NOTE: GameObj is responsible for the obstacles inside.*/
private:
};