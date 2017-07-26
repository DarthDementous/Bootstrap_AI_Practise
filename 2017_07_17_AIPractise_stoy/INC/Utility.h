#pragma once

// Default values
#define PLAYER_RADIUS	8.f
#define PLAYER_FRICTION	1.f
#define PLAYER_REBOUND_STRENGTH 100.f

#define NODE_RADIUS 8.f

#define ARROW_RADIUS NODE_RADIUS / 4

#define SEARCH_RADIUS 100.f
#define SEARCH_NODE m_graph->GetNodes()->at(0)

#define GRAPH_START_X 100
#define GRAPH_START_Y getWindowHeight() - 100
#define GRAPH_WIDTH 3
#define GRAPH_HEIGHT 3
#define GRAPH_OFFSET_X -50
#define GRAPH_OFFSET_Y 50
#define GRAPH_SPACING 100

#define SEEK_STRENGTH 100.f
#define FLEE_STRENGTH -100.f
#define SEEK_RADIUS 15
#define FLEE_RADIUS 250

#define PATH_DIST_CHANGE 20.f