#pragma once

#include "IBehaviour.hpp"

class Path;

class FollowPath : public IBehaviour {
public:
	FollowPath(size_t a_currPathIndex = 0, Path* a_path = nullptr) : m_currPathIndex(a_currPathIndex), m_path(a_path) {}
	virtual ~FollowPath();

	virtual void Update(GameObj* a_obj, float a_dt);
	virtual void Render(GameObj* a_obj, aie::Renderer2D* a_r2d);

	void SetPath(Path* a_path) { m_path = a_path; }
	
	const Path* GetPath() { return m_path; }
protected:
	Path* m_path;						/*Does not have ownership, is just pointing to it.*/

	size_t m_currPathIndex;				/*What numbered node an entity is currently targeting.*/
private:
};