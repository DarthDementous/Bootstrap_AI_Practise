#pragma once

#include "GameObj.hpp"
#include "Utility.h"

namespace aie {
	class Renderer2D;
}

class GameStateManager;
class IObstacle;
class IGameState;
class IBehaviour;

/**
*	@brief Interface base class for entities that move with behaviours.
*/
class IAgent : public GameObj {
public:
	IAgent(const glm::vec2 & a_pos = glm::vec2(0.f, 0.f), float a_friction = PLAYER_FRICTION);
	virtual ~IAgent();

	virtual void Update(float a_dt);
	virtual void Render(aie::Renderer2D* a_r2d);

	const glm::vec2& GetPosition() { return m_pos; }
	const glm::vec2& GetVelocity() { return m_vel; }
	float GetFriction() { return m_friction; }
	std::vector<IObstacle*>& GetObstacles() { return m_obstacles; }
	GameStateManager* GetStateManager() { return m_stateManager; }

	void SetPosition(glm::vec2& a_pos) { m_pos = a_pos; }
	void SetVelocity(glm::vec2& a_vel) { m_vel = a_vel; }
	void SetFriction(float a_frict) { m_friction = a_frict; }
	/**
	*	@brief Change and clear currently held vector of obstacles.
	*	@param a_obs is the vector of obstacles to assign.
	*	@return void.
	*/
	void SetObstacles(std::vector<IObstacle*> a_obs);

	/**
	*	@brief Increase acceleration by applying an additional movement vector.
	*/
	void ApplyForce(glm::vec2& a_force) { m_accel += a_force; }

	/**
	*	@brief Calculates trajectory for update frame based on velocity, acceleration and friction.
	*	@param a_dt is the time between frames for normalising calculations.
	*	@return void.
	*/
	void ApplyPhysics(float a_dt);
protected:
	GameStateManager* m_stateManager = nullptr;				/*Handles update/rendering/changing etc. of states.*/

	glm::vec2	m_pos;										/*Object's current position.*/
	glm::vec2	m_vel;										/*Trajectory of object for each frame.*/
	glm::vec2	m_accel;									/*Modifier to velocity calculated this frame.*/

	float		m_friction;									/*Scale of negative velocity applied to slow object down.*/

	std::vector<IObstacle*> m_obstacles;					/*Vector of obstacles to avoid. NOTE: IAgent is NOT responsible for the obstacles inside.*/
private:
};