#pragma once

#include "GameObj.hpp"
#include "Utility.h"

namespace aie {
	class Renderer2D;
}

class GameStateManager;
class IObstacle;
class IGameState;

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
	*	@brief Set behaviour from list of given behaviours.
	*	@param a_name is the name of the behaviour to set. (must already be added)
	*	@param a_replace determines whether it pops the current active state before setting (true) or adds to active behaviours (false).
	*/
	void SetBehaviour(const char* a_name, bool a_replace);

	/**
	*	@brief Add behaviour to list of possible behaviours.
	*	@param a_name is the key to identify the behaviour with.
	*	@param a_beh is the behaviour to push to the behaviour manager.
	*/
	void AddBehaviour(const char* a_name, IGameState* a_beh);

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
	GameStateManager* m_behaviourManager = nullptr;			/*Handles update/rendering/changing etc. of behaviours.*/

	glm::vec2	m_pos;										/*Object's current position.*/
	glm::vec2	m_vel;										/*Trajectory of object for each frame.*/
	glm::vec2	m_accel;									/*Modifier to velocity calculated this frame.*/

	float		m_friction;									/*Scale of negative velocity applied to slow object down.*/

	std::vector<IObstacle*> m_obstacles;					/*Vector of obstacles to avoid. NOTE: IAgent is responsible for the obstacles inside.*/
private:
};