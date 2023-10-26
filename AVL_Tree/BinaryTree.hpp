#pragma once
#ifndef BINARYTREE_HPP
# define BINARYTREE_HPP

#include <iostream>
#include <stack>
#include <queue>

class Node {
	public:
		Node(int x) {
			data = x;
			height = 1;
			left = nullptr;
			right = nullptr;
		}
		~Node() {}
		// int getBF(Node *);
		// int calculateHeight();
		Node *getPredecessor();
		Node *getSuccessor();
		void updateHeight();

		int data;
		int height;
		Node *left;
		Node *right;
};

class AVLTree {
	public:
		AVLTree();
		~AVLTree();
		Node *insert(Node *, int);
		Node *remove(Node *, int);
		void display(Node *, int);
		static void	delete_tree(Node *);
		Node *root;

	private:
		Node *LLRotation(Node *);
		Node *LRRotation(Node *);
		Node *RLRotation(Node *);
		Node *RRRotation(Node *);
};

#endif