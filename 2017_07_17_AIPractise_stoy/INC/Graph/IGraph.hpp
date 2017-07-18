#pragma once

#include <vector>


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
		Node(T a_data) : m_data(a_data) {
			m_edges = new std::vector<Edge*>;
		}

		~Node() {
			m_edges->clear();
			delete m_edges;
		}

		T& GetData() { return m_data; }
		std::vector<Edge*>* GetEdges() { return m_edges; }

		T m_data;
		std::vector<Edge*>* m_edges = nullptr;
	};

	struct Edge {
		Edge(bool a_directed, Node* a_to, float a_weight, Node* a_from = nullptr) : m_directed(a_directed), m_to(a_to), m_weight(a_weight), m_from(a_from) {}

		bool IsDirected() { return m_directed; }

		Node* m_to;					 /*Node at the end of the connection.*/
		Node* m_from;				 /*Node at the beginning of the connection. (Only available if edge is not directed).*/

		float m_weight;				 /*Cost to traverse this edge.*/

		bool m_directed;			 /*true = edge can only traverse to next node, false = edge can traverse to the next node and back to the previous.*/
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
		m_nodes->push_back(a_node);
	}

	/**
	*	@brief Create an edge from two nodes and add it to the graph.
	*	@param a_nodeA is the starting vertice of the edge.
	*	@param a_nodeB is the end vertice of the edge.
	*	@param a_directed is whether the edge can be traversed both ways or only one way.
	*	@param a_weight is the cost to traverse the edge.
	*	@return void.
	*/
	void AddEdge(Node* a_nodeA, Node* a_nodeB, bool a_directed, float a_weight = 0) {
		// Find relevant nodes by de-referencing iterator
		Node* foundNodeA = *(std::find(m_nodes->begin(), m_nodes->end(), a_nodeA));		
		Node* foundNodeB = *(std::find(m_nodes->begin(), m_nodes->end(), a_nodeB));

 		// Directed, add edge to the first node
		if (a_directed) {
			foundNodeA->m_edges->push_back(new Edge(a_directed, a_nodeB, a_weight));						// Don't specify where it's coming from since its not two-way.
		}
		// Un-directed, add edge to both nodes
		else {
			foundNodeA->m_edges->push_back(new Edge(a_directed, a_nodeB, a_weight, a_nodeA));				// Specify where its coming from because it is two-way.
			foundNodeB->m_edges->push_back(new Edge(a_directed, a_nodeB, a_weight, a_nodeA));			
		}

	}

protected:
	std::vector<Node*>* m_nodes = nullptr;		/*List of vertices on the graph.*/
private:
};