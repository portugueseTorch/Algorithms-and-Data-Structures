#pragma once
#ifndef BINARYTREE_HPP
# define BINARYTREE_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class Node {
	public:
		Node(int x) {
			data = x;
			left = NULL;
			right = NULL;
		}
		~Node() {}
		int		data;
		Node	*left;
		Node	*right;
};

class BinaryTree {
	public:
		BinaryTree();
		BinaryTree(Node *);
		BinaryTree(vector<int> &);
		~BinaryTree();
		void	insert(int);
		Node	*del(Node *, int);
		void	delete_tree(Node *);
		Node	*getHead() { return head; }

		// TreeTraversal.cpp
		void	level_display();
		void	display_tree(Node *, int);
		void	preorder_recursive(Node *);
		void	inorder_recursive(Node *);
		void	postorder_recursive(Node *);
		void	preorder_iterative();
		void	inorder_iterative();
		void	postorder_iterative();
		int		height(Node *);
		int		size(Node *);
		int		leaf_nodes(Node *);
		int		non_leaf_nodes(Node *);

		// BinarySearchTree.cpp
		Node	*binarySearchR(Node *, int);
		Node	*binarySearchI(int);
		void	insertI(int);
		void	insertR(Node *, Node *, int);

	private:
		Node	*head;

};

#endif