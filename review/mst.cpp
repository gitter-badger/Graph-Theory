#include <iostream>
#include <limits.h>

using namespace std;

#define V 6

int minKey(int key[], bool mstSet[]) {
	int min = INT_MAX;
	int min_index;
	for (int v = 0; v < V; v++) {
		if (mstSet[v] == false && key[v] < min) {
			min = key[v];
			min_index = v;
		}
	}
	return min_index;
}

void printMST(int parent[], int graph[V][V]) {
	cout << "Edge Weight" << endl;
	for (int i = 1; i < V; i++) {
		cout << parent[i] << "-" << i << "  " << graph[i][parent[i]] << endl;
	}
}

void primMST(int graph[V][V]) {
	bool mstSet[V];
	int key[V];
	int parent[V];

	for (int v = 0; v < V; v++) {
		mstSet[v] = false;
		key[v] = INT_MAX;
	}

	key[0] = 0;
	parent[0] = -1;

	for (int i = 0; i < V-1; i++) {
		int v = minKey(key, mstSet);
		mstSet[v] = true;
		for (int u = 0; u < V; u++) {
			if (graph[v][u] && mstSet[u] == false && graph[v][u] < key[u]) {
				key[u] = graph[v][u];
				parent[u] = v;
			}
		}
	}

	printMST(parent, graph);
}	

int main() {
	int graph[V][V] = {
		{0, 6, 1, 5, 0, 0},
		{6, 0, 5, 0, 3, 0},
		{1, 5, 0, 5, 6, 4},
		{5, 0, 5, 0, 0, 2},
		{0, 3, 6, 0, 0, 6},
		{0, 0, 4, 2, 6, 0}
	};
	primMST(graph);
	return 0;
}