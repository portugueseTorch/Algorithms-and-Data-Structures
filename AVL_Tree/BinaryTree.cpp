#include "BinaryTree.hpp"

using namespace std;

int	getHeight(Node *node) {
	return node ? node->height : 0;
}

int getBF(Node *node) {
	return node ? (getHeight(node->left) - getHeight(node->right)) : 0;
}

void Node::updateHeight() {
	height = max(getHeight(left), getHeight(right)) + 1;
}

AVLTree::AVLTree() {
	root = NULL;
}

void AVLTree::delete_tree(Node *root) {
	if (!root) return;
	delete_tree(root->left);
	delete_tree(root->right);
	delete root;
}

AVLTree::~AVLTree() {
	delete_tree(root);
}

Node *AVLTree::LLRotation(Node *node) {
	Node *node_l = node->left;
	Node *node_lr = node->left->right;

	node->left = node_lr;
	node_l->right = node;

	// Recalculate height
	node->updateHeight();
	node_l->updateHeight();

	if (node == root)
		root = node_l;

	return node_l;
}

Node *AVLTree::LRRotation(Node *node) {
	Node *node_l = node->left;
	Node *node_lr = node->left->right;

	node->left = node_lr->right;
	node_l->right = node_lr->left;
	node_lr->right = node;
	node_lr->left = node_l;
	
	// Recalculate height
	node->updateHeight();
	node_l->updateHeight();
	node_lr->updateHeight();

	if (node == root)
		root = node_lr;

	return node_lr;
}

Node *AVLTree::RLRotation(Node *node) {
	Node *node_r = node->right;
	Node *node_rl = node->right->left;

	node->right = node_rl->left;
	node_r->left = node_rl->right;
	node_rl->left = node;
	node_rl->right = node_r;

	// Recalculate height
	node->updateHeight();
	node_r->updateHeight();
	node_rl->updateHeight();

	if (node == root)
		root = node_rl;

	return node_rl;
}

Node *AVLTree::RRRotation(Node *node) {
	Node *node_r = node->right;
	Node *node_rl = node->right->left;

	node->right = node_rl;
	node_r->left = node;

	// Recalculate height
	node->updateHeight();
	node_r->updateHeight();

	if (node == root)
		root = node_r;

	return node_r;
}

Node *Node::getPredecessor() {
	Node *p = this->left;
	while (p && p->right)
		p = p->right;
	return p;
}

Node *Node::getSuccessor() {
	Node *p = this->right;
	while (p && p->left)
		p = p->left;
	return p;
}

Node *search(Node *node, int key, int reps = 1) {
	if (!node) return NULL;
	if (key < node->data)
		return search(node->left, key, reps + 1);
	else if (key > node->data)
		return search(node->right, key, reps + 1);
	else {
		cout << "Found " << key << " in " << reps << " comps" << endl;
		return node;
	}
}

Node *AVLTree::insert(Node *node, int key) {
	if (!node) {
		Node *new_node = new Node(key);
		if (!root)
			root = new_node;
		return new_node;
	}

	if (key < node->data)
		node->left = insert(node->left, key);
	else if (key > node->data)
		node->right = insert(node->right, key);
	else return node;

	// Recalculate height
	node->updateHeight();
	if (getBF(node) == 2 && getBF(node->left) == 1)
		return LLRotation(node);
	else if (getBF(node) == 2 && getBF(node->left) == -1)
		return LRRotation(node);
	else if (getBF(node) == -2 && getBF(node->right) == 1)
		return RLRotation(node);
	else if (getBF(node) == -2 && getBF(node->right) == -1)
		return RRRotation(node);
	
	return node;
}

Node *AVLTree::remove(Node *node, int key) {
	if (!node) return NULL;
	if (!node->left && !node->right && node->data == key) {
		if (node == root)
			root = NULL;
		delete node;
		return NULL;
	}

	if (key < node->data)
		node->left = remove(node->left, key);
	else if (key > node->data)
		node->right = remove(node->right, key);
	else {
		if (getHeight(node->left) > getHeight(node->right)) {
			Node *pre = node->getPredecessor();
			node->data = pre->data;
			node->left = remove(node->left, pre->data);
		} else {
			Node *suc = node->getSuccessor();
			node->data = suc->data;
			node->right = remove(node->right, suc->data);
		}
	}

	node->updateHeight();
	// if (getBF(node) == 2 && getBF(node->left) == 1)
	// 	return LLRotation(node);
	// else if (getBF(node) == 2 && getBF(node->left) == -1)
	// 	return LRRotation(node);
	// else if (getBF(node) == 2 && getBF(node->left) == 0)
	// 	return LLRotation(node);
	// else if (getBF(node) == -2 && getBF(node->left) == 0)
	// 	return RRRotation(node);
	// else if (getBF(node) == -2 && getBF(node->right) == 1)
	// 	return RLRotation(node);
	// else if (getBF(node) == -2 && getBF(node->right) == -1)
	// 	return RRRotation(node);

	return node;
}

void display(Node *node, int spaces) {
	if (!node) return;
	display(node->right, spaces + 1);
	for (int i = 0; i < spaces; i++) cout << "      ";
	cout << node->data << endl;
	display(node->left, spaces + 1);
}

void AVLTree::display(Node *node, int spaces = 0) {
	if (!node) return;
	display(node->right, spaces + 1);
	for (int i = 0; i < spaces; i++) cout << "      ";
	cout << node->data << endl;
	display(node->left, spaces + 1);
}

int main() {
	AVLTree tree;

	// cout << "Inserting 10:" << endl;
	// tree.insert(tree.root, 10);
	// tree.display(tree.root);
	// cout << "############################" << endl;
	// cout << "Inserting 20:" << endl;
	// tree.insert(tree.root, 20);
	// tree.display(tree.root);
	// cout << "############################" << endl;
	// cout << "Inserting 30:" << endl;
	// tree.insert(tree.root, 30);
	// tree.display(tree.root);
	// cout << "############################" << endl;
	// cout << "Inserting 50:" << endl;
	// tree.insert(tree.root, 50);
	// tree.display(tree.root);
	// cout << "############################" << endl;
	// cout << "Inserting 40:" << endl;
	// tree.insert(tree.root, 40);
	// tree.display(tree.root);
	// cout << "############################" << endl;
	// cout << "Inserting 60:" << endl;
	// tree.insert(tree.root, 60);
	// tree.display(tree.root);
	// cout << "############################" << endl;
	// cout << "Inserting 70:" << endl;
	// tree.insert(tree.root, 70);
	// tree.display(tree.root);
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

	tree.insert(tree.root, 13);
	tree.insert(tree.root, 11);
	tree.insert(tree.root, 9);
	// tree.insert(tree.root, 7);
	// tree.insert(tree.root, 6);
	// tree.insert(tree.root, 4);
	// tree.insert(tree.root, 2);
	// tree.insert(tree.root, 1);
	// tree.insert(tree.root, 0);
	// tree.insert(tree.root, -1);
	// tree.insert(tree.root, -2);
	display(tree.root, 0);
	search(tree.root, -2);
	cout << "############################" << endl;
	// tree.remove(tree.root, 6);
	// tree.display(tree.root, 0);
	// cout << "############################" << endl;
	// tree.remove(tree.root, 7);
	// tree.display(tree.root, 0);
	// cout << "############################" << endl;
	// tree.remove(tree.root, 4);
	// tree.display(tree.root, 0);
	// cout << "############################" << endl;
	// tree.remove(tree.root, 2);
	// tree.display(tree.root, 0);
	// cout << "############################" << endl;
	// tree.remove(tree.root, -1);
	// tree.display(tree.root, 0);
	// cout << "############################" << endl;
	// tree.remove(tree.root, 1);
	// tree.display(tree.root, 0);
	// cout << "############################" << endl;
	// tree.remove(tree.root, 9);
	// tree.display(tree.root, 0);
	// cout << "############################" << endl;
	// tree.remove(tree.root, 11);
	// tree.display(tree.root, 0);
	// cout << "############################" << endl;
	// tree.remove(tree.root, 0);
	// tree.display(tree.root, 0);
	// cout << "############################" << endl;
	// tree.remove(tree.root, 13);
	// tree.display(tree.root, 0);
	// cout << "############################" << endl;
	// tree.remove(tree.root, -2);
	// tree.display(tree.root, 0);

	return 0;
}
