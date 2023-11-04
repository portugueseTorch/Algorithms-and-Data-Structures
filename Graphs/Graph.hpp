#pragma once
#ifndef GRAPH_HPP
# define GRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <stack>
#include <queue>
#include <limits>

#define INF	numeric_limits<int>::max()

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
		Node(int n, int i): data(n), id(i) {}
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
			cout << data << " (" << this << "), id: " << id << endl;
			for (auto edge : edges)
				edge.display();
			cout << endl;
		}

		int getEdgeWeight(int n) {
			for (auto edge : edges) {
				if (edge.node->data == n)
					return edge.weight;
			}
			return INF;
		}

		int data;
		int id;
		list<Edge> edges;
};

void Edge::display() {
	cout << "\t[ data: " << node->data << " (" << node << "), id: "<< node->id << ", weight: " << weight << " ]" << endl;
}

class AbstractGraph {
	public:
		AbstractGraph() = default;
		~AbstractGraph() = default;

		void addEdge(int from, int to, int weight) {
			// If either from or to don't yet exist, create and add them to adjecency list
			if (adjecency_list.count(from) == 0) {
				adjecency_list[from] = Node(from, ++num_vertices);
				db.push_back(from);
			}
			if (adjecency_list.count(to) == 0) {
				adjecency_list[to] = Node(to, ++num_vertices);
				db.push_back(to);
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

	protected:
		vector<int> db;
		int num_vertices = 0;
		unordered_map<int,Node> adjecency_list;
};

#endif
