#include "Graph.hpp"

class DFSGraph : public AbstractGraph {
	public:
		void iterativeDFS() {
			stack<int> s;
			unordered_map<int,bool> visited;

			s.push(db.front());
			visited[db.front()] = true;
			while (!s.empty()) {
				Node &cur = adjecency_list[s.top()];
				s.pop();
				cout << cur.data << " ";

				for (auto edge : cur.edges) {
					if (visited.count(edge.node->data) == 0) {
						s.push(edge.node->data);
						visited[edge.node->data] = true;
					}
				}
			}
			cout << endl;
		}

		void recursiveDFS(Node *node) {
			static unordered_map<int,bool> visited;

			if (visited.count(node->data) == 0) {
				visited[node->data] = true;
				cout << node->data << " ";
				for (auto edge : node->edges)
					if (visited.count(edge.node->data) == 0)
						recursiveDFS(edge.node);
			}
		}
};

int main() {
	DFSGraph graph;

	graph.addEdge(1, 2, 0);
	graph.addEdge(1, 3, 0);
	graph.addEdge(2, 4, 0);
	graph.addEdge(3, 4, 0);
	graph.addEdge(4, 5, 0);
	graph.addEdge(4, 6, 0);

	graph.display();

	graph.iterativeDFS();
	graph.recursiveDFS(graph.getFirst());
	cout << endl;

	return 0;
}
