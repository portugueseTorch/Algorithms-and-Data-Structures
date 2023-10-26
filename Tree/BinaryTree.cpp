#include "BinaryTree.hpp"

BinaryTree::BinaryTree() {
	int value;
	Node *p, *t;
	queue<Node *>	q;
	cout << "Enter root value: ";
	cin >> value;
	head = new Node(value);
	q.push(head);
	while (!q.empty()) {
		p = q.front();
		q.pop();
		cout << "Insert left node of " << p->data << ": ";
		cin >> value;
		if (value != -1) {
			t = new Node(value);
			p->left = t;
			q.push(t);
		}
		cout << "Insert right node of " << p->data << ": ";
		cin >> value;
		if (value != -1) {
			t = new Node(value);
			p->right = t;
			q.push(t);
		}
	}
}

BinaryTree::BinaryTree(Node *node) {
	head = node;
}

BinaryTree::BinaryTree(vector<int> &vec) {
	head = NULL;
	for (int num : vec) insert(num);
}

BinaryTree::~BinaryTree() {
	delete_tree(head);
}

void BinaryTree::insert(int x) {
	if (!head) {
		head = new Node(x);
		return ;
	}

	Node *p = head, *q = NULL;
	while (p) {
		q = p;
		if (x < p->data)
			p = p->left;
		else if (x > p->data)
			p = p->right;
		else return;
	}
	x < q->data ? q->left = new Node(x) : q->right = new Node(x);
	return ;
}

void	BinaryTree::delete_tree(Node *head) {
	if (!head) return;
	delete_tree(head->left);
	delete_tree(head->right);
	delete head;
}

void	BinaryTree::display_tree(Node *node, int spaces) {
	if (!node) return;
	display_tree(node->right, spaces + 1);
	for (int i = 0; i < spaces; i++) cout << "      ";
	cout << node->data << endl;
	display_tree(node->left, spaces + 1);
}
