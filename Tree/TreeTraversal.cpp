#include "BinaryTree.hpp"

void	BinaryTree::preorder_recursive(Node *node) {
	if (!node) return;
	cout << node->data << " ";
	preorder_recursive(node->left);
	preorder_recursive(node->right);
}

void	BinaryTree::inorder_recursive(Node *node) {
	if (!node) return;
	inorder_recursive(node->left);
	cout << node->data << " ";
	inorder_recursive(node->right);
}

void	BinaryTree::postorder_recursive(Node *node) {
	if (!node) return;
	postorder_recursive(node->left);
	postorder_recursive(node->right);
	cout << node->data << " ";
}

void	BinaryTree::level_display() {
	if (!head) return ;
	Node *p;
	queue<Node *> que;
	cout << head->data << " ";
	que.push(head);
	while (!que.empty()) {
		p = que.front();
		que.pop();
		if (!p)
			continue;
		if (p->left) {
			cout << p->left->data << " ";
			que.push(p->left);
		}
		if (p->right) {
			cout << p->right->data << " ";
			que.push(p->right);
		}
	}
	cout << endl;
}

void	BinaryTree::preorder_iterative() {
	if (!head) return;
	stack<Node *> st;
	Node *p = head;
	while (p || !st.empty()) {
		if (!p) {
			p = st.top();
			st.pop();
			p = p->right;
		} else {
			st.push(p);
			cout << p->data << " ";
			p = p->left;
		}
	}
	cout << endl;
}

void	BinaryTree::inorder_iterative() {
	if (!head) return;
	stack<Node *> st;
	Node *p = head;
	while (p || !st.empty()) {
		if (!p) {
			p = st.top();
			st.pop();
			cout << p->data << " ";
			p = p->right;
		} else {
			st.push(p);
			p = p->left;
		}
	}
	cout << endl;
}

void	BinaryTree::postorder_iterative() {
	if (!head) return;
	stack<long int> st;
	long int address;
	Node *p = head;
	while (p || !st.empty()) {
		if (!p) {
			address = st.top();
			st.pop();
			if (address < 0) {
				cout << ((Node *) -address)->data << " ";
				p = NULL;
			} else {
				st.push(-address);
				p = ((Node *) address)->right;
			}
		} else {
			st.push((long int) p);
			p = p->left;
		}
	}
	cout << endl;
}

int BinaryTree::height(Node *node) {
	if (!node) return 0;
	int left_subtree, right_subtree;
	left_subtree = height(node->left);
	right_subtree = height(node->right);
	return max(left_subtree, right_subtree) + 1;
}

int BinaryTree::size(Node *node) {
	if (!node) return 0;
	int left_subtree, right_subtree;
	left_subtree = size(node->left);
	right_subtree = size(node->right);
	return left_subtree + right_subtree + 1;
}

int BinaryTree::leaf_nodes(Node *node) {
	if (!node) return 0;
	int left_subtree, right_subtree;
	left_subtree = leaf_nodes(node->left);
	right_subtree = leaf_nodes(node->right);
	if (left_subtree + right_subtree == 0)
		return 1;
	else
		return left_subtree + right_subtree;
}

int BinaryTree::non_leaf_nodes(Node *node) {
	if (!node) return 0;
	int left_subtree, right_subtree;
	left_subtree = non_leaf_nodes(node->left);
	right_subtree = non_leaf_nodes(node->right);
	if (node->left || node->right)
		return left_subtree + right_subtree + 1;
	else
		return left_subtree + right_subtree;
}

// int main() {
// 	BinaryTree tree;
// 	cout << endl;
// 	tree.display_tree(tree.getHead(), 0);
// 	cout << endl;

// 	cout << "Tree height: " << tree.height(tree.getHead()) << endl;
// 	cout << "Tree size: " << tree.size(tree.getHead()) << endl;
// 	cout << "Number of leafs: " << tree.leaf_nodes(tree.getHead()) << endl;
// 	cout << "Number of non-leafs: " << tree.non_leaf_nodes(tree.getHead()) << endl;

// 	return 0;
// }
