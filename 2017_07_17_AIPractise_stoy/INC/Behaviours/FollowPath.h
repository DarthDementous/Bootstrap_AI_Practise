#pragma once

#include "IBehaviour.hpp"

class Path;

class FollowPath : public IBehaviour {
public:
	FollowPath(IAgent* a_obj = nullptr, size_t a_currPathIndex = 0, Path* a_path = nullptr) : 
		IBehaviour(a_obj), m_currPathIndex(a_currPathIndex), m_path(a_path) {}
	virtual ~FollowPath();

	virtual void Initialise() {}
	virtual void Startup() {}
	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D* a_r2d);
	virtual void Shutdown() {}

	void SetPath(Path* a_path);
	
	const Path* GetPath() { return m_path; }
protected:
	Path* m_path;						/*Does not have ownership, is just pointing to it.*/

	size_t m_currPathIndex;				/*What numbered node an entity is currently targeting.*/
private:
};