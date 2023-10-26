#include "BinaryTree.hpp"

Node *BinaryTree::binarySearchR(Node *node, int x) {
	if (!node) return NULL;
	if (x < node->data)
		return binarySearchR(node->left, x);
	else if (x > node->data)
		return binarySearchR(node->right, x);
	else
		return node;
}

Node *BinaryTree::binarySearchI(int x) {
	Node *p = getHead();
	while (p) {
		if (p->data > x)
			p = p->left;
		else if (p->data < x)
			p = p->right;
		else
			return p;
	}
	return NULL;
}

void BinaryTree::insertI(int x) {
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

void BinaryTree::insertR(Node *node, Node *trailing, int x) {
	if (!node)
		x < trailing->data ? trailing->left = new Node(x) : trailing->right = new Node(x);
	else if (x < node->data)
		insertR(node->left, node, x);
	else if (x > node->data)
		insertR(node->right, node, x);
}

Node *get_predecessor(Node *node) {
	while (node && node->right)
		node = node->right;
	return node;
}

Node *get_successor(Node *node) {
	while (node && node->left)
		node = node->left;
	return node;
}

Node *BinaryTree::del(Node *node, int key) {
	if (!node) return NULL;
	if (!node->right && !node->left && node->data == key) {
		if (head == node)
			head = NULL;
		delete(node);
		return NULL;
	}
	if (key < node->data)
		node->left = del(node->left, key);
	else if (key > node->data)
		node->right = del(node->right, key);
	else {
		if (height(node->left) > height(node->right)) {
			Node *pre = get_predecessor(node->left);
			node->data = pre->data;
			node->left = del(node->left, pre->data);
		} else {
			Node *suc = get_successor(node->right);
			node->data = suc->data;
			node->right = del(node->right, suc->data);
		}
	}
	return node;
}

Node *tree_from_preorder(vector<int> &vec) {
	stack<Node *> st;
	Node *head = new Node(vec.at(0));
	Node *p = head;

	st.push(p);
	int i = 1;
	while (i < vec.size()) {
		if (vec[i] < p->data) {
			p->left = new Node(vec[i]);
			st.push(p);
			p = p->left;
			i++;
		} else if (vec[i] > p->data) {
			if (st.empty() || st.top()->data > vec[i]) {
				p->right = new Node(vec[i]);
				p = p->right;
				i++;
			} else {
				p = st.top();
				st.pop();
			}
		} else
			i++;
	}
	return head;
}

int main() {
	vector<int> vec = {7, 5, 1, 8, 3, 6, 0, 9, 4, 2};
	BinaryTree tree(vec);

	cout << endl;
	tree.display_tree(tree.getHead(), 0);


	return 0;
}
