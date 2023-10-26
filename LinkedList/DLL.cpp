#include <iostream>

using namespace std;

class Node {
	public:
		Node(int x) {
			data = x;
			prev = NULL;
			next = NULL;
		}
		~Node() {}
		int data;
		Node *prev;
		Node *next;
};

class DoubleLinkedList {
	public:
		DoubleLinkedList();
		DoubleLinkedList(int arr[], int n);
		~DoubleLinkedList();
		Node *head() { return _head; }
		void display();
		void reverseDisplay();
		void insert(int pos, int x);
		void remove(int x);
		void reverse();
		int length();
		Node *getMiddle();

	private:
		Node *_head;
};

DoubleLinkedList::DoubleLinkedList() {
	_head = NULL;
}

DoubleLinkedList::DoubleLinkedList(int arr[], int n) {
	Node *last;

	last = new Node(arr[0]);
	_head = last;
	for (int i = 1; i < n; i++) {
		Node *new_node = new Node(arr[i]);
		last->next = new_node;
		new_node->prev = last;
		last = new_node;
	}
}

DoubleLinkedList::~DoubleLinkedList() {
	for (Node *tmp = head(); tmp;) {
		Node *to_del = tmp;
		tmp = tmp->next;
		delete to_del;
	}
}

void DoubleLinkedList::display() {
	for (Node *tmp = head(); tmp; tmp = tmp->next)
		cout << tmp->data << " ";
	cout << endl;
}

void DoubleLinkedList::reverseDisplay() {
	Node *p = head();
	for (; p->next; p = p->next);
	for (; p != NULL; p = p->prev)
		cout << p->data << " ";
	cout << endl;
}

void DoubleLinkedList::insert(int pos, int x) {
	if (pos < 0 || pos > length()) return ;

	Node *new_node = new Node(x);
	if (!head()) {
		_head = new_node;
		return ;
	} else if (pos == 0) {
		new_node->next = _head;
		_head->prev = new_node;
		_head = new_node;
	} else {
		Node *p = head();
		for (int i = 0; i < pos - 1; i++) p = p->next;
		new_node->next = p->next;
		if (p->next) p->next->prev = new_node;
		new_node->prev = p;
		p->next = new_node;
	}
}

int DoubleLinkedList::length() {
	int len = 0;
	for (Node *p = head(); p; p = p->next)
		len++;
	return len;
}

void DoubleLinkedList::remove(int x) {
	if (!_head) return ;

	Node *p = _head, *tmp;
	while (p) {
		if (p->data == x) {
			if (p == _head) {
				if (p->next) p->next->prev = NULL;
				_head = p->next;
			} else {
				if (p->prev) p->prev->next = p->next;
				if (p->next) p->next->prev = p->prev;
			}
			tmp = p->next;
			delete p;
			p = tmp;
		} else { 
			p = p->next;
		}
	}
}

void DoubleLinkedList::reverse() {
	if (!_head) return ;

	Node *p = _head, *tmp = NULL;
	while (p) {
		tmp = p->prev;
		p->prev = p->next;
		p->next = tmp;
		if (!p->prev)
			_head = p;
		p = p->prev;
	}
}

Node *DoubleLinkedList::getMiddle() {
	if (!_head) return NULL;

	Node *p = _head, *q = _head;
	while (p && p->next) {
		p = p->next;
		if (p) p = p->next;
		q = q->next;
	}
	return q;
}

int main() {
	int arr[] = { 1, 4, 7, 9, 11, 14, 18 };
	DoubleLinkedList list(arr, sizeof(arr)/sizeof(*arr));

	// list.insert(2, 19);
	list.display();

	cout << "Middle element: " << list.getMiddle()->data << endl;

	return 0;
}
