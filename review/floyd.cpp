#include <iostream>

using namespace std;

#define V 3
#define INF 99999

void printSolution(int dist[V][V]) {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF) {
				cout << "INF" << " ";
			}
			else {
				cout << dist[i][j] << " ";
			}
		}
		cout << endl;
	}
}

void floyd(int graph[V][V]) {
	int dist[V][V];
	
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			dist[i][j] = graph[i][j];
		}
	}

	for (int k = 0; k < V; k++) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	printSolution(dist);
}

int main() {
	int graph[V][V] = {
		{0, 4, 5},
        {2, 0, INF},
        {INF, -3, 0},
    };
    floyd(graph);
	return 0;
}