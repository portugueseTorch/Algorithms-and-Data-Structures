#include <iostream>
#include <stack>
#include <queue>
#include <stdlib.h> 

using namespace std;

enum Color {
	Black,
	Red
};

class Node {
	public:
		Node(int n) {
			data = n;
			left = NULL;
			right = NULL;
			color = Red;
		}

		void recolor() {
			if (color == Red) color = Black;
			else color = Red;
		}

		Node *getPredecessor() {
			Node *node = left;
			while (node && node->right)
				node = node->right;
			return node;
		}

		Node *getSuccessor() {
			Node *node = right;
			while (node && node->left)
				node = node->left;
			return node;
		}

		static bool hasChildren(Node *node) {
			return node && (node->left || node->right);
		}

		static bool hasGrandchildren(Node *node) {
			return node && ((node->left && (node->left->left || node->left->right)) \
				|| (node->right && (node->right->right || node->right->left)));
		}

		int		data;
		Color	color;
		Node	*left;
		Node	*right;
};

class RBTree {
	public:
		RBTree() { root = NULL; }
		~RBTree() { deleteTree(root); }

		void deleteTree(Node *node) {
			if (!node) return ;
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
		}

		static void display(Node *node, int spaces = 0) {
			if (!node) return;
			display(node->right, spaces + 1);
			for (int i = 0; i < spaces; i++) cout << "      ";
			if (node->color == Red) cout << "\033[1;31m" << node->data << "\033[0m" << endl;
			else cout << "\033[1;30m" << node->data << "\033[0m" << endl;
			display(node->left, spaces + 1);
		}

		Node *insert(Node *node, int key) {
			if (!node) {
				Node *new_node = new Node(key);
				if (!root) {
					new_node->recolor();
					root = new_node;
				}
				return new_node;
			}
			if (key < node->data)
				node->left = insert(node->left, key);
			else if ( key > node->data)
				node->right = insert(node->right, key);
			else return node;

			// Apply rotation if need be
			display(node);
			node = balanceTree(node);
			if (node == root && node->color == Red) node->recolor();
			return node;
		}

		Node *root;

	private:
		Node *LLrotation(Node *node) {
			Node *node_l = node->left;
			Node *node_lr = node->left->right;

			node->left = node_lr;
			node_l->right = node;

			// Recolor
			node_l->recolor();
			node_l->right->color = Red;

			if (node == root)
				root = node_l;

			return node_l;
		}

		Node *LRrotation(Node *node) {
			Node *node_l = node->left;
			Node *node_lr = node->left->right;

			node->left = node_lr->right;
			node_l->right = node_lr->left;
			node_lr->right = node;
			node_lr->left = node_l;

			// Recolor
			node_lr->recolor();
			node_lr->right->color = Red;

			if (node == root)
				root = node_lr;

			return node_lr;
		}

		Node *RLrotation(Node *node) {
			Node *node_r = node->right;
			Node *node_rl = node->right->left;

			node->right = node_rl->left;
			node_r->left = node_rl->right;
			node_rl->left = node;
			node_rl->right = node_r;

			// Recolor
			node_rl->recolor();
			node_rl->left->color = Red;

			if (node == root)
				root = node_rl;

			return node_rl;
		}

		Node *RRrotation(Node *node) {
			Node *node_r = node->right;
			Node *node_rl = node->right->left;

			node->right = node_rl;
			node_r->left = node;

			// Recolor
			node_r->recolor();
			node_r->left->color = Red;

			if (node == root)
				root = node_r;

			return node_r;
		}

		Node *recolor(Node *node) {
			node->left->recolor();
			node->right->recolor();
			node->recolor();
			return node;
		}

		Node *balanceTree(Node *node) {
			if (!node ) return NULL;

			// If the node is leaf or doesn't have grandchildren, return
			if (!Node::hasGrandchildren(node)) return node;

			// Check imbalances on the left side (LL and LR scenario)
			if (node->left) {
				if (node->left->left) {
					// LL scenario
					if (node->left->color == Red && node->left->left->color == Red) {
						if (node->right && node->right->color == Red)
							node = recolor(node);
						// Else, perform LL rotation on node
						else
							node = LLrotation(node);
						return node;
					}
				} else if (node->left->right) {
					// LR scenario
					if (node->left->color == Red && node->left->right->color == Red) {
						if (node->right && node->right->color == Red)
							node = recolor(node);
						// Else, perform LL rotation on node
						else
							node = LRrotation(node);
						return node;
					}
				}
			}
			if (node->right) {
				if (node->right->right) {
					// RR scenario
					if (node->right->color == Red && node->right->right->color == Red) {
						if (node->left && node->left->color == Red)
							node = recolor(node);
						// Else, perform RR rotation on node
						else
							node = RRrotation(node);
						return node;
					}
				} else if (node->right->left) {
					// RL scenario
					if (node->right->color == Red && node->right->left->color == Red) {
						if (node->left && node->left->color == Red)
							node = recolor(node);
						// Else, perform RL rotation on node
						else
							node = RLrotation(node);
						return node;
					}
				}
			}
			return node;
		}
};

int main() {
	RBTree tree;
	cout << "Inserting 2:" << endl;
	tree.insert(tree.root, 2);
	tree.display(tree.root);
	cout << "############################" << endl;
	cout << "Inserting 1:" << endl;
	tree.insert(tree.root, 1);
	tree.display(tree.root);
	cout << "############################" << endl;
	cout << "Inserting 4:" << endl;
	tree.insert(tree.root, 4);
	tree.display(tree.root);
	cout << "############################" << endl;
	cout << "Inserting 5:" << endl;
	tree.insert(tree.root, 5);
	tree.display(tree.root);
	cout << "############################" << endl;
	cout << "Inserting 9:" << endl;
	tree.insert(tree.root, 9);
	tree.display(tree.root);
	cout << "############################" << endl;
	cout << "Inserting 3:" << endl;
	tree.insert(tree.root, 3);
	tree.display(tree.root);
	cout << "############################" << endl;
	cout << "Inserting 6:" << endl;
	tree.insert(tree.root, 6);
	tree.display(tree.root);
	cout << "############################" << endl;
	cout << "Inserting 7:" << endl;
	tree.insert(tree.root, 7);
	tree.display(tree.root);
	cout << "############################" << endl;
	cout << "Inserting 11:" << endl;
	tree.insert(tree.root, 11);
	tree.display(tree.root);
	// cout << "############################" << endl;
	// cout << "Inserting 80:" << endl;
	// tree.insert(tree.root, 80);
	// tree.display(tree.root);
	// cout << "############################" << endl;
	// cout << "Inserting 4:" << endl;
	// tree.insert(tree.root, 4);
	// tree.display(tree.root);
	// cout << "############################" << endl;
	// cout << "Inserting 8:" << endl;
	// tree.insert(tree.root, 8);
	// tree.display(tree.root);
	// cout << "############################" << endl;
	// cout << "Inserting 2:" << endl;
	// tree.insert(tree.root, 2);
	// tree.display(tree.root);
	// cout << "############################" << endl;

	return 0;
}

