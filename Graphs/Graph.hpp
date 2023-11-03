#pragma once
#ifndef GRAPH_HPP
# define GRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <stack>
#include <queue>

using namespace std;
class Node;

class Edge {
	public:
		Edge(Node *n, int w): node(n), weight(w) {}
		~Edge() = default;

		void display();
		Node *node;
		int weight;
};

class Node {
	public:
		Node() {}
		Node(int n): data(n) {}
		~Node() = default;

		void addEdge(Node *node, int weight) {
			edges.push_back(Edge(node, weight));
		}

		bool connected(int n) {
			for (auto edge : edges)
				if (edge.node->data == n) return true;
			return false;
		}

		void display() {
			cout << data << " (" << this << ")" << endl;
			for (auto edge : edges)
				edge.display();
			cout << endl;
		}

		int data;
		list<Edge> edges;
};

void Edge::display() {
	cout << "\t[ data: " << node->data << " (" << node << "), weight: " << weight << " ]" << endl;
}

class Graph {
	public:
		Graph() = default;
		~Graph() = default;

		void addEdge(int from, int to, int weight) {
			// If either from or to don't yet exist, create and add them to adjecency list
			if (adjecency_list.count(from) == 0) {
				adjecency_list[from] = Node(from);
				db.push_back(from);
				cout << "Created " << from << endl;
			}
			if (adjecency_list.count(to) == 0) {
				adjecency_list[to] = Node(to);
				db.push_back(to);
				cout << "Created " << to << endl;
			}

			Node &from_node = adjecency_list[from];
			Node &to_node = adjecency_list[to];

			// Check if the nodes are already connected
			if (from_node.connected(to))
				return;

			// Add the edges to both graphs
			from_node.addEdge(&to_node, weight);
			to_node.addEdge(&from_node, weight);
		}

		Node *getFirst() {
			return &adjecency_list[db.front()];
		}

		void display() {
			for (int num : db)
				adjecency_list[num].display();
		}

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

	private:
		vector<int> db;
		unordered_map<int,Node> adjecency_list;
};

#endif
