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
		// Save node to each line
		for (auto node : *m_nodes) {
			/*
			62, 100 = representation of node
			< = begin edge section
			| = seperate connected node
			*/

			// Add current node (has to be done and in the same place because temporary buffers required, MUST NOT be deleted until exiting this function.
			char nodeData[256];
			sprintf_s(nodeData, "%4.2f,%4.2f", node->GetData().x, node->GetData().y);
			graphFile << nodeData;

			auto edges = node->GetEdges();
			if (!edges->empty()) {
				// Begin edge section
				graphFile << "<";

				for (size_t i = 0; i < edges->size(); ++i) {
					// Add edge data
					char connectedNodeData[256];
					auto connectedNode = edges->at(i)->m_to;
					sprintf_s(connectedNodeData, "%4.2f,%4.2f", connectedNode->GetData().x, connectedNode->GetData().y);
					
					graphFile << connectedNodeData;

					if (connectedNode->GetData().y == 4294967040) {
						bool stop;
						stop = true;
					}

					// Add seperator if not last
					if (i != node->GetEdges()->size() - 1) {
						graphFile << "|";
					}
				}
			}
			// End line
			graphFile << "\n";
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
	m_nodes->clear();

	if (graphFile.is_open()) {
		// Read file line by line as strings
		std::string line;
		while (std::getline(graphFile, line)) {
			// Create vectors by sectioning the line appropriately
			auto splitLine = Util::StringToVector(line, '<');
			auto homeNodeText = Util::StringToVector(splitLine[0], ',');
			// Make sure there is an edge section before splitting it
			std::vector<std::string> edgeSect;
			if (splitLine.size() == 2) {
				edgeSect = Util::StringToVector(splitLine[1], '|');
			}

			// Convert string to vector 2 and add home node
			Node* homeNode = new Node(glm::vec2(std::stof(homeNodeText[0]), std::stof(homeNodeText[1])));
			AddNode(homeNode);

			// Loop through edge section and add possible edges
			for (auto edgeText : edgeSect) {
				auto edgeNodeText = Util::StringToVector(edgeText, ',');
				Node* edgeNode = new Node(glm::vec2(std::stof(edgeNodeText[0]), std::stof(edgeNodeText[1])));
				AddNode(edgeNode);

				AddEdge(homeNode, edgeNode, true, glm::length(edgeNode->GetData() - homeNode->GetData()));
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
