#include "Graph\Graph2D.h"
#include <glm/gtx/norm.hpp>
#include <Input.h>
#include <iostream>
#include <fstream>


void Graph2D::Update()
{
	aie::Input* input = aie::Input::getInstance();
	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);

	/// Left click
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
		//// Add node
		if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT)) {
			Graph2D::Node* newNode = new Graph2D::Node(glm::vec2(mouseX, mouseY));
			AddNode(newNode);

			// Connect node to nearby ones via edges weighted by distance
			for (auto nearNode : GetNearbyNodes(glm::vec2(mouseX, mouseY), SEARCH_RADIUS / 2)) {
				// Don't let node connect to itself
				if (nearNode == newNode) {
					continue;
				}
				AddEdge(nearNode, newNode, true, glm::length(nearNode->GetData() - newNode->GetData()));
			}
		}
	}

	/// Save
	if (input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL) && input->wasKeyPressed(aie::INPUT_KEY_S)) {
		SaveToFile("./test.txt");
		std::cout << "Saved Graph" << std::endl;
	}

	/// Load
	if (input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL) && input->wasKeyPressed(aie::INPUT_KEY_L)) {
		LoadFromFile("./test.txt");
		std::cout << "Loaded Graph" << std::endl;
	}

}

void Graph2D::SaveToFile(const char* a_filename)
{
	std::ofstream graphFile;
	
	// Create/open file in specified directory
	graphFile.open(a_filename, std::ios::out);

	if (graphFile.is_open()) {
		/*
		NODES:
		x y
		EDGES:
		0 1 true 0
		*/
		/// Nodes
		graphFile << "NODES:" << "\n";

		for (auto node : *m_nodes) {
			// Add current node as a string: "x y" 
			char nodeData[256];
			sprintf_s(nodeData, "%4.2f %4.2f", node->GetData().x, node->GetData().y);
			graphFile << nodeData << "\n";		// Move to next line
		}

		/// Edges
		graphFile << "EDGES:" << "\n";

		for (auto node : *m_nodes) {
			for (auto edge : *node->GetEdges()) {
				// 0(fromID) 1(toID) true 200.f
				char edgeData[256];
				const char* bidirected = edge->IsBidirected() ? "true" : "false";	// Convert bool to string to add it as text
				sprintf_s(edgeData, "%i %i %s %4.2f", node->GetID(), edge->m_to->GetID(), bidirected, edge->GetWeight());

				graphFile << edgeData << "\n";
			}
		}
	}
			
	graphFile.flush();
	graphFile.close();

}

void Graph2D::LoadFromFile(const char * a_filename)
{
	//Test if the file directory is valid (returns boolean)
	std::fstream graphFile(a_filename, std::ios::in);	
	assert(graphFile && "Graph file not found.");

	// Prepare graph for new nodes
	Clear();

	if (graphFile.is_open()) {
		// Read each line of file as strings
		std::vector <std::string> lines;
		std::string line;

		// Process lines according to their section
		bool inNodes = false;
		bool inEdges = false;

		while (std::getline(graphFile, line)) {

			/// At node header
			if (line == "NODES:") {
				// Continue to node section
				inNodes = true;
				continue;
			}
			/// At edge header
			else if (line == "EDGES:") {
				// Continue to edge section (always after nodes)
				inNodes = false;
				inEdges = true;
				continue;
			}

			// Split line by spaces
			auto splitLine = Util::StringToVector(line, ' ');

			/// Node
			if (inNodes) {
				// Line meets requirements to be processed as a node
				if (splitLine.size() >= 2) {
					// 402.00[0] 20.00[1] ... 
					AddNode(new Node(glm::vec2(std::stof(splitLine[0]), std::stof(splitLine[1]))));	// Convert strings to floats			
				}
			}
			/// Edge
			if (inEdges) {
				// Line meets requirements to be processed as an edge
				if (splitLine.size() >= 4) {
					// fromID[0] toID[1] bidirectedBool[2] weight[3] ...
					bool bidirected = splitLine[2] == "true" ? true : false;
					AddEdge(GetNodeByID(std::stoi(splitLine[0])), GetNodeByID(std::stoi(splitLine[1])), bidirected, std::stof(splitLine[3])); // String conversions: int, bool, float
				}
			}

		}
	}

	graphFile.close();

}

std::vector<Graph2D::Node*> Graph2D::GetNearbyNodes(glm::vec2& a_pos, float a_radius)
{
	std::vector<Graph2D::Node*> nearbyNodes;

	// Loop through all nodes and add those within the given range
	for (auto node : *m_nodes) {
		// Find magnitude of vector between circle origins. glm::length(v) INSTEAD of v.length(), the latter gives the dimension instead.
		auto distance = glm::length(node->GetData() - a_pos);

		if (distance < node->GetRadius() + a_radius) {
			nearbyNodes.push_back(node);
		}
	}

	return nearbyNodes;
}
