#include "Graph.hpp"


class Graph : public AbstractGraph {
	public:
		Node &getNodeById(int id) {
			for (auto num : db) {
				Node &node = adjecency_list[num];
				if (node.id == id)
					return node;
			}
			return *getFirst();
		}

		Graph *primMST() {
			Graph *new_graph = new Graph;
			int near[num_vertices + 1];
			Node *cur;
			for (int i = 0; i < num_vertices + 1; i++) near[i] = INF;

			// Find minimum cost edge
			pair<int,vector<Node*>> min_edge = first_min_cost();

			// Add edge to the new graph
			new_graph->addEdge(min_edge.second.at(0)->data, min_edge.second.at(1)->data, min_edge.first);

			// Update Current node
			cur = min_edge.second.at(0);

			// Update near
			near[min_edge.second.at(0)->id] = 0;
			near[min_edge.second.at(1)->id] = 0;
			for (int i = 1; i < num_vertices + 1; i++) {
				if (near[i] == 0) continue;
				else if (near[i] != INF) {
					Node &node = getNodeById(i);
					if (node.connected(cur->data) && \
						node.getEdgeWeight(cur->data) < node.getEdgeWeight(getNodeById(near[i]).data))
						near[i] = cur->id;
				} else {
					if (cur->connected(getNodeById(i).data))
						near[i] = cur->id;
					else
						near[i] = min_edge.second.at(1)->id;
				}
			}

			for (int i = 0; i < num_vertices - 2; i++) {
				// Find minimum edge from near
				min_edge = find_min_edge(near);
				if (min_edge.first == INF) {
					delete new_graph;
					return NULL;
				}

				// Add edge to the new graph
				new_graph->addEdge(min_edge.second.at(0)->data, min_edge.second.at(1)->data, min_edge.first);

				// Update Current node
				cur = min_edge.second.at(0);

				// Update near
				near[min_edge.second.at(0)->id] = 0;
				for (int i = 1; i < num_vertices + 1; i++) {
					if (near[i] == 0) continue;
					Node &node = getNodeById(i);
					if (node.connected(cur->data) && \
						node.getEdgeWeight(cur->data) < node.getEdgeWeight(getNodeById(near[i]).data))
						near[i] = cur->id;
				}
			}

			return new_graph;
		}

	private:
		// Returns a vector with data of nodes associated with the minimum edge
		pair<int,vector<Node*>> first_min_cost() {
			pair<int,vector<Node*>> min;
			min.first = INF;

			// For each vector
			for (auto num : db) {
				Node &node = adjecency_list[num];
				// For each edge of the current vector
				for (auto edge : node.edges) {
					// If current edge weight is less than prev min, update it
					if (edge.weight < min.first) {
						min.first = edge.weight;
						min.second = { &node, edge.node };
					}
				}
			}
			return min;
		}

		pair<int,vector<Node*>> find_min_edge(int *near) {
			pair<int,vector<Node*>> min;
			min.first = INF;
			min.second = { NULL, NULL };

			for (int i = 1; i < num_vertices + 1; i++) {
				if (near[i] == 0) continue;
				Node &node = getNodeById(i);
				Node &cmp_to = getNodeById(near[i]);
				if (node.connected(cmp_to.data) && node.getEdgeWeight(cmp_to.data) < min.first) {
					min.first = node.getEdgeWeight(cmp_to.data);
					min.second = { &node, &cmp_to };
				}
			}
			return min;
		}
};

int main() {
	Graph graph;

	graph.addEdge(10, 20, 25);
	graph.addEdge(50, 70, 18);
	graph.addEdge(70, 20, 10);
	graph.addEdge(10, 60, 5);
	graph.addEdge(60, 50, 20);
	graph.addEdge(30, 20, 12);
	graph.addEdge(70, 40, 14);
	graph.addEdge(40, 30, 8);
	graph.addEdge(50, 40, 16);

	Graph *new_graph = graph.primMST();
	if (new_graph) new_graph->display();

	return 0;
}

