#include <iostream>
#include <limits.h>

using namespace std;

#define V 9

int minDistance(int dist[], bool sptSet[]) {
	int min = INT_MAX;
	int min_index;
 
   	for (int v = 0; v < V; v++) {
     	if (sptSet[v] == false && dist[v] < min) {
         	min = dist[v];
         	min_index = v;
     	}
   	}
 
   	return min_index;
}

void printSolution(int dist[]) {
	cout << "Vertex  Distance from source" << endl;
	for (int i = 0; i < V; i++) {
		cout << i << "       " << dist[i] << endl;
	}
}

void dijsktra(int graph[V][V], int src) {
	int dist[V];
	bool sptSet[V];

	for (int v = 0; v < V; v++) {
		dist[v] = INT_MAX;
		sptSet[v] = false;
	}

	dist[src] = 0;

	for (int count = 0; count < V-1; count++) {
		int v = minDistance(dist, sptSet);
		sptSet[v] = true;
		for (int u = 0; u < V; u++) {
			if (sptSet[u] == false && graph[v][u] && dist[v] + graph[v][u] < dist[u]) {
				dist[u] = dist[v] + graph[v][u];
			}
		}
	}

	printSolution(dist);
}

int main() {
	int graph[V][V] = {
		{0, 4, 0, 0, 0, 0, 0, 8, 0},
       	{4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 0, 10, 0, 2, 0, 0},
        {0, 0, 0, 14, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };
    dijsktra(graph, 0);
	return 0;
}