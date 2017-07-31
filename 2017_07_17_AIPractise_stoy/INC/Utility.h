#pragma once

#include <vector>
#include <sstream>
#include <string>

// Default values
#define PLAYER_FORCE 1000.f
#define PLAYER_RADIUS	8.f
#define PLAYER_FRICTION	1.f
#define PLAYER_REBOUND_STRENGTH 100.f

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
};

