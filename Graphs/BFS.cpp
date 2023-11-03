#include "Graph.hpp"

int main() {
	Graph graph;

	graph.addEdge(1, 2, 0);
	graph.addEdge(1, 3, 0);
	graph.addEdge(2, 4, 0);
	graph.addEdge(3, 4, 0);
	graph.addEdge(4, 5, 0);
	graph.addEdge(4, 6, 0);

	graph.display();

	graph.BFS();
	graph.iterativeDFS();
	graph.recursiveDFS(graph.getFirst());
	return 0;
}