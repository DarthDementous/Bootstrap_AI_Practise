#pragma once

#include "GameObj.h"
#include "Graph/Graph2D.h"

class FollowPath;
class Seek;
class KeyboardController;
class Path;
class PathFinder;
class Wander;

/**
*	@brief Entity designed to represent the user in the game space that inherits from the GameObj interface class.
*/
class Player : public GameObj {
public:
	Player(glm::vec2& a_pos = glm::vec2(0, 0), glm::vec2& a_vel = glm::vec2(0, 0), float a_friction = PLAYER_FRICTION, IBehaviour* a_behaviour = nullptr);
	virtual ~Player();

	virtual void Update(float a_dt);
	virtual void Render(aie::Renderer2D* a_r2d);

	/**
	*	@brief Activates the seek behaviour and seeks specified target.
	*	@param a_target is the vector 2 position the entity will move towards.
	*/
	void SeekTarget(glm::vec2& a_target);

	void SetPathFinder(PathFinder* a_pf) { m_pathFinder = a_pf; }
protected:
	//Hold onto variable for each wanted behaviour to avoid initialising once every update frame
	Seek*					m_seekBehaviour		= nullptr;								
	KeyboardController*		m_controlBehaviour	= nullptr;
	FollowPath*				m_followBehaviour	= nullptr;
	Wander*					m_wanderBehaviour	= nullptr;

	Path*		m_path		 = nullptr;		/*Player is responsible for deleting this.*/
	PathFinder* m_pathFinder = nullptr;

	Graph2D::Node* m_startNode	= nullptr;
	Graph2D::Node* m_goalNode	= nullptr;
private:
};