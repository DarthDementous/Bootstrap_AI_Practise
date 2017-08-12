#pragma once

#include <vector>
#include <sstream>
#include <string>
#include <MathLib_Utility.h>
#include <glm/vec2.hpp>
#include <glm/gtx/normalize_dot.hpp>
#include <algorithm>

class Circle;
class Tri;
class Rect;

enum eSearchResult { FOUND, SEARCHING, NOT_FOUND};
enum eCollisionType { INTERSECTS, ADJUST, CONTAINS, NONE };

// Default values
#define MESSAGE_LIFETIME 3.0

#define NPC_NUM 1u
#define OBSTACLE_NUM 10u

#define CIRCLE_RAD 30.f
#define RECT_EXTENTS glm::vec2(100.f, 100.f)

#define HEURISTIC_FUNC [this](Graph2D::Node* a_node){ return Math_Util::Magnitude(m_goalNode->GetData() - a_node->GetData()); }

#define ARRIVAL_MIN 0.001f

#define DEFAULT_COLLISION_RAYS 3

#define FOV_RANGE 45.f
#define LOS_LENGTH 100.f

#define RAND_VEC_MIN -10
#define RAND_VEC_MAX 10

#define RAND_PI_MIN -628
#define RAND_PI_MAX 628

#define GLOBAL_RESTITUTION 1.f

#define WANDER_TIMER .3f
#define PATH_TIMER 60.f

#define PLAYER_FORCE 500.f
#define PLAYER_RADIUS	8.f
#define PLAYER_FRICTION	1.f
#define PLAYER_REBOUND_STRENGTH 100.f
#define PLAYER_JITTER 5.f
#define PLAYER_WANDER_RADIUS 100.f
#define PLAYER_WANDER_DIST 150.f

#define NODE_RADIUS 8.f

#define ARROW_RADIUS NODE_RADIUS / 4

// No higher than 150.f or else it'll skip to the second node if its in a straight line due to it drawing a more efficient connection to that node.
#define SEARCH_RADIUS 150.f
#define SEARCH_NODE m_graph->GetNodes()->at(0)

// NOTE: If number is not negative the expression will be made unsigned int by default leading to wrap around - make sure these are floats!
#define GRAPH_START_X 100.f
#define GRAPH_START_Y getWindowHeight() - 100.f
#define GRAPH_WIDTH 10u
#define GRAPH_HEIGHT 6u
#define GRAPH_OFFSET_X -50.f
#define GRAPH_OFFSET_Y 50.f
#define GRAPH_SPACING 100.f

#define SEEK_STRENGTH 100.f
#define FLEE_STRENGTH -100.f
#define SEEK_RADIUS 15
#define FLEE_RADIUS 250

#define PATH_CHANGE_DIST 20.f

/**
*	@brief Static utility class with helpful functions.
*	NOTE: Functions are wrapped up in a class to avoid linker errors of multiply defined symbols.
*/
class Util {
public:
	/// Credit to: http://code.runnable.com/VHb0hWMZp-ws1gAr/splitting-a-string-into-a-vector-for-c%2B%2B
	/**
	*	@brief Take in a string and split it by a given delimiter
	*	@param a_str is the string to split.
	*	@param a_delim is the char that defines the split.
	*	@return vector of split strings.
	*/
	static std::vector<std::string> StringToVector(std::string a_str, char a_delim) {
		std::vector<std::string> split;
		// Convert to string stream to allow for easy splitting
		std::stringstream ss(a_str);
		std::string tok;				/*Token (split part of string)*/

		// Use tokens and getline function to split and add to vector
		while (std::getline(ss, tok, a_delim)) {
			split.push_back(tok);
		}

		return split;
	}

	/**
	*	@brief Determine state of collision with point vs a circle
	*	@param a_pt is the point used in the collision.
	*	@param a_circle is the circle used in the collision.
	*	@return enum of type of collision: 0 = INTERSECTS, 1 = ADJUST, 2 = CONTAINS, 3 = NONE
	*/
	static unsigned int PointVsCircle(glm::vec2& a_pt, Circle* a_circle);

	/**
	*	@brief Determine state of collision with point vs a rectangle.
	*	@param a_pt is the point used in the collision.
	*	@param a_rect is the rectangle used in the collision.
	*	@return enum of type of collision: 0 = INTERSECTS, 1 = ADJUST, 2 = CONTAINS, 3 = NONE
	*/
	static unsigned int PointVsRect(glm::vec2& a_pt, Rect* a_rect);

	/**
	*	@brief Determine state of collision with point vs a triangle.
	*	@param a_pt is the point used in the collision.
	*	@param a_tri is the triangle used in the collision.
	*	@return enum of type of collision: 0 = INTERSECTS, 1 = ADJUST, 2 = CONTAINS, 3 = NONE
	*/
	static unsigned int PointVsTri(glm::vec2& a_pt, Tri* a_tri);

	/**
	*	@brief Check if two points are on the same side of a line.
	*	@param a_pt1 is the first point to check.
	*	@param a_pt2 is the second point to check.
	*	@param a_lineStart is the beginning of the line.
	*	@param a_lineEnd is the end of the line.
	*	@return true if points on same side, else false.
	*/
	static bool SameSideOfLine(glm::vec2& a_pt1, glm::vec2& a_pt2, glm::vec2& a_lineStart, glm::vec2& a_lineEnd);

	/**
	*	@brief Calculate the imaginary z axis of the perpendicular vector (useful for determining whether a point is in front or behind a line.
	*	@param a_vec1 is the first vector.
	*	@param a_vec2 is the second vector.
	*	@return a scalar representing the imaginary z axis of the perpendicular vector.
	*/
	static float CrossProduct(glm::vec2& a_vec1, glm::vec2& a_vec2);

	/**
	*	@brief Calculate the mid-point of a vector.
	*	@param a_start is the starting point of the vector.
	*	@param a_head is the end point of the vector.
	*	@return mid-point of the vector of the two points.
	*/
	static glm::vec2 LinearHalfPoint(glm::vec2& a_start, glm::vec2& a_head);

	struct Ray {
		Ray(glm::vec2 a_origin, glm::vec2& a_dir, float a_length = 0) : origin(a_origin), dir(a_dir), length(a_length) {}

		/**
		*	@brief Cast out ray using variables.
		*	@return Constructed ray vector.
		*/
		glm::vec2 CalculateVector() {
			return glm::vec2(dir * length);
		}

		float length;				/*Max distance vector can be cast out to.*/
		glm::vec2 origin;			/*The point the origin is cast out from.*/
		glm::vec2 dir;				/*Direction of ray.*/
		bool HasCollided = false;	/*Whether ray has collided or not.*/
	};

	/**
	*	@brief Keep value within specified min and max range.
	*	@param a_clampVal is the value to clamp.
	*	@param a_min is the minimum range
	*	@param a_max is the maximum range
	*	@return clamped value.
	*/
	static float Clamp(float a_clampVal, float a_min, float a_max) {
		float result = std::max(a_min, std::min(a_clampVal, a_max));
		
		return result;
	}

	/**
	*	@brief Determine possible collision with ray and find point of collision on ray.
	*	@param a_ray is the ray used in the calculations.
	*	@param a_pt is the point used in the calculations.
	*	@return point of collision on the ray. If no collision, vector will be zeroed.
	*/
	static glm::vec2 FindCollisionPointOnRay(Ray& a_ray, glm::vec2 a_pt) {
		glm::vec2 collisionVector = a_pt - a_ray.origin;							/*Vector between ray origin and point of collision*/

		// Clamp dot product between collision vector and ray direction
		float projLength = Clamp(glm::dot(collisionVector, a_ray.dir), 0.f, a_ray.length);

		return a_ray.origin + a_ray.dir * projLength;
	}


};

