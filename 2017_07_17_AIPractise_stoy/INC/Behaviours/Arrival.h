#pragma once

#include "IBehaviour.hpp"
#include <functional>

/**
*	@brief Behaviour that makes an object go towards a destination and slow down to a stop when within a certain radius.
*/
class Arrival : public IBehaviour {
public:
	Arrival();
	~Arrival();
protected:
	float m_radius;		/*Size of radius to start slowing down object.*/

	std::function<void()> m_withinRadiusFunc;	/*Call when within radius.*/
	std::function<void()> m_reachPointFunc;		/*Call once upon reaching specified point.*/
private:
};