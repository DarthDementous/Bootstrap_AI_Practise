#pragma once

#include <vector>
#include "Utility.h"

/**
*	@brief Interface class that holds nodes with un-directed/directed edges.
*/
template<class T> class IGraph {
public:
	/// Forward declarations
	struct Node;
	struct Edge;

public:
	struct Node {
	public:
		Node(T& a_data, float a_radius = NODE_RADIUS) : m_data(a_data), m_radius(a_radius) {
			m_edges = new std::vector<Edge*>;
		}

		~Node() {
			m_edges->clear();
			delete m_edges;
		}

		T& GetData() { return m_data; }
		const float GetRadius() { return m_radius; }
		const size_t GetID() { return m_id; }
		const std::vector<Edge*>* GetEdges() { return m_edges; }

		size_t m_id;
		std::vector<Edge*>* m_edges = nullptr;
	private:
		T m_data;
		float m_radius;
	};

	struct Edge {
	public:
		Edge(bool a_bidirected, Node* a_to, float a_weight, Node* a_from = nullptr) : m_bidirected(a_bidirected), m_to(a_to), m_weight(a_weight), m_from(a_from) {}

		bool IsBidirected() { return m_bidirected; }

		Node* m_to;					 /*Node at the end of the connection.*/
		Node* m_from;				 /*Node at the beginning of the connection. (Only available if edge is not directed).*/

		float m_weight;				 /*Cost to traverse this edge.*/
	private:
		bool m_bidirected;			 /*true = edge can traverse to the next node and back to the previous, false = edge can only traverse to next node. */
	};

public:
	IGraph() {
		// Initialize list of nodes
		m_nodes = new std::vector<Node*>;
	}
	

	virtual ~IGraph() {
		// Erase all nodes in vector and their edges
		m_nodes->clear();

		// Free up memory held by vector
		delete m_nodes;
	}

	std::vector<Node*>* GetNodes() { return m_nodes; }

	/**
	*	@brief Add a node to the graph.
	*	@param a_node is the node to add.
	*	@return void.
	*/
	void AddNode(Node* a_node) {
		// Apply id to node in order of it being added for easier identification.
		static size_t count = 0;
		
		a_node->m_id = count++;
		m_nodes->push_back(a_node);

	}

	/**
	*	@brief Create an edge from two nodes and add it to the graph.
	*	@param a_nodeA is the starting vertice of the edge.
	*	@param a_nodeB is the end vertice of the edge.
	*	@param a_bidirected is whether the edge can be traversed both ways or only one way.
	*	@param a_weight is the cost to traverse the edge.
	*	@return void.
	*/
	void AddEdge(Node* a_nodeA, Node* a_nodeB, bool a_bidirected, float a_weight = 0) {
		// Find relevant nodes by de-referencing iterator
		Node* foundNodeA = *(std::find(m_nodes->begin(), m_nodes->end(), a_nodeA));		
		Node* foundNodeB = *(std::find(m_nodes->begin(), m_nodes->end(), a_nodeB));

 		// Bidirected, add edge to both nodes
		if (a_bidirected) {
			foundNodeA->m_edges->push_back(new Edge(a_bidirected, a_nodeB, a_weight, a_nodeA));		// Specify where its coming from because it is two-way.
			foundNodeB->m_edges->push_back(new Edge(a_bidirected, a_nodeB, a_weight, a_nodeA));
		}
		// Directed, add edge to one node
		else {
			foundNodeA->m_edges->push_back(new Edge(a_bidirected, a_nodeB, a_weight));				// Don't specify where it's coming from since its not two-way
		}

	}

protected:
	std::vector<Node*>* m_nodes = nullptr;		/*List of vertices on the graph.*/
private:
};