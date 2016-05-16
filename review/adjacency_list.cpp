#include <fstream>
#include <iostream>

using namespace std;

struct Node {
	int vertex;
	Node* next;
	Node(int vertex, Node* next) {
		this->vertex = vertex;
		this->next = next;
	}
};

class Graph {
private:
	int V;
	Node* list[100];
public:
	Graph(int V);
	~Graph();
	int addEdge(int src, int dest);
	void printGraph();
};

Graph::Graph(int V) {
	this->V = V;
	for (int i = 0; i < this->V; i++) {
		this->list[i] = new Node(i, NULL);
	}
}

Graph::~Graph() {
	for (int i = 0; i < this->V; i++) {
		while (this->list[i]->next) {
			Node* temp = this->list[i];
			this->list[i] = this->list[i]->next;
			delete temp;
		}
		delete this->list[i];	
	}
	this->V = 0;
}

int Graph::addEdge(int src, int dest) {
	Node* newNode = new Node(dest, this->list[src]);
	this->list[src] = newNode;

	// Since graph is undirected, add an edge from dest to src also.
	newNode = new Node(src, this->list[dest]);
	this->list[dest] = newNode;
	return 1;
}

void Graph::printGraph() {
	cout << this->V << endl;
	for (int i = 0; i < this->V; i++) {
		Node* temp = this->list[i];
		while (temp->next) {
			cout << temp->vertex << " ";
			temp = temp->next;
		}
		cout << endl;
	}
}

int main() {
	Graph g(5);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(0, 3);
	g.addEdge(0, 4);
	g.addEdge(1, 3);
	g.addEdge(2, 3);
	g.addEdge(2, 4);
	g.addEdge(3, 4);
	g.printGraph();
	return 0;
}
