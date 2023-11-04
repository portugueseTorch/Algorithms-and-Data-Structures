#include "Graph.hpp"

class BFSGraph : public AbstractGraph {
	public:
		void BFS() {
			queue<int> q;
			unordered_map<int,bool> visited;

			q.push(db.front());
			visited[db.front()] = true;

			while (!q.empty()) {
				Node &cur = adjecency_list[q.front()];
				q.pop();
				cout << cur.data << " ";

				for (auto edge : cur.edges) {
					if (visited.count(edge.node->data) == 0) {
						q.push(edge.node->data);
						visited[edge.node->data] = true;
					}
				}
			}
			cout << endl;
		}
};

int main() {
	BFSGraph graph;

	graph.addEdge(1, 2, 0);
	graph.addEdge(1, 3, 0);
	graph.addEdge(2, 4, 0);
	graph.addEdge(3, 4, 0);
	graph.addEdge(4, 5, 0);
	graph.addEdge(4, 6, 0);

	graph.display();

	graph.BFS();

	return 0;
}
