#include <iostream>

using namespace std;

class Node {
	public:
		Node(int x) { data = x; next = NULL; }
		~Node() {}
		int		data;
		Node	*next;
};

class LinkedList {
	public:
		LinkedList();
		~LinkedList();

		Node *head;
		Node *last;

		void addFront(int x);
		void addBack(int x);
		void insert(int pos, int x);
		void insertSorted(int x);
		void removeDuplicates();
		void reverseCopy();
		void reverseLinks();
		void reverseRecursive(Node *curr, Node *prev);
		void display();
		void remove(int x);
		void join(LinkedList &other);
		void merge(LinkedList &other);
		bool isSorted();
		bool isLoop();
		int getSum();
		int length();
};

LinkedList::LinkedList() {
	head = NULL;
}

LinkedList::~LinkedList() {
	Node *tmp;
	for (Node *it = head; it;) {
		tmp = it->next;
		delete it;
		it = tmp;
	}
	head = NULL;
}

int LinkedList::length() {
	int i = 0;
	for (Node *it = head; it; it = it->next)
		i++;
	return i;
}

void LinkedList::addFront(int x) {
	if (!head) {
		head = new Node(x);
		return ;
	}

	Node *new_head = new Node(x);
	new_head->next = head;
	head = new_head;
}

void LinkedList::addBack(int x) {
	if (!head) {
		head = new Node(x);
		return ;
	}

	Node *tmp = head;
	for (; tmp->next; tmp = tmp->next);
	tmp->next = new Node(x);
}

void LinkedList::insert(int pos, int x) {
	if (pos < 0 || pos > length()) return ;

	if (pos == 0) {
		addFront(x);
	} else {
		Node *new_node = new Node(x);
		Node *tmp = head;
		for (int i = 0; i < pos - 1; i++)
			tmp = tmp->next;
		new_node->next = tmp->next;
		tmp->next = new_node;
	}
}

// 5
// 1 4 8 16 24
void LinkedList::insertSorted(int x) {
	if (!head) {
		addFront(x);
		return ;
	}

	Node *p = head, *q = NULL;
	Node *new_node = new Node(x);
	while (p && p->data < x) {
		q = p;
		p = p->next;
	}
	if (p == head) {
		new_node->next = head;
		head = new_node;
	} else {
		q->next = new_node;
		new_node->next = p;
	}
}

void LinkedList::display() {
	for (Node *it = head; it; it = it->next)
		cout << it->data << " ";
	cout << endl;
}

void LinkedList::remove(int x) {
	if (!head) return ;

	Node *p = head, *q = NULL;
	while (p) {
		if (p->data == x) {
			if (q == NULL) {
				head = p->next;
				delete p;
				p = head;
			} else {
				q->next = p->next;
				delete p;
				p = q->next;
			}
		} else {
			q = p;
			p = p->next;
		}
	}
}

int LinkedList::getSum() {
	int sum = 0;
	for (Node *it = head; it; it = it->next)
		sum += it->data;
	return sum;
}

bool LinkedList::isSorted() {
	if (!head) return false;
	int prev = head->data;
	Node *it = head->next;
	for (; it; it = it->next) {
		if (it->data < prev) return false;
		prev = it->data;
	}
	return true;
}

void LinkedList::removeDuplicates() {
	if (!head) return ;

	Node *p = head->next, *q = head;
	while (p) {
		if (q->data == p->data) {
			q->next = p->next;
			delete p;
			p = q->next;
		} else {
			q = p;
			p = p->next;
		}
	}
}

void LinkedList::reverseCopy() {
	if (!head) return ;

	int arr[length()];
	int i = 0;
	for (Node *p = head; p; p = p->next)
		arr[i++] = p->data;

	i--;
	for (Node *p = head; p; p = p->next)
		p->data = arr[i--];
}

void LinkedList::reverseLinks() {
	if (!head) return ;

	Node *p = head, *q = NULL, *r = NULL;

	while (p) {
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	head = q;
}

void LinkedList::reverseRecursive(Node *curr, Node *prev) {
	if (!curr) {
		head = prev;
		return ;
	}
	reverseRecursive(curr->next, curr);
	curr->next = prev;
}

void LinkedList::join(LinkedList &other) {
	if (!head) {
		head = other.head;
		other.head = NULL;
		return ;
	}

	Node *p = head;
	while (p->next)
		p = p->next;
	p->next = other.head;
	other.head = NULL;
}

void LinkedList::merge(LinkedList &other) {
	if (!head) {
		head = other.head;
		other.head = NULL;
		return ;
	}

	Node *first = head, *second = other.head, *last = NULL;

	if (first->data < second->data) {
		last = first;
		first = first->next;
	} else {
		last = second;
		second = second->next;
	}
	last->next = NULL;

	while (first && second) {
		if (first->data < second->data) {
			last->next = first;
			first = first->next;
		} else {
			last->next = second;
			second = second->next;
		}
		last = last->next;
		last->next = NULL;
	}
	if (first) last->next = first;
	else last->next = second;
	other.head = NULL;
}

bool LinkedList::isLoop() {
	if (!head) return false;

	Node *p = head, *q = head;
	do {
		p = p->next;
		q = q->next;
		if (q) q = q->next;
		if (q == p) break;
	} while (p && q);
	return q == p && q != NULL;
}

int main() {
	LinkedList list1;
	list1.addBack(1);
	list1.addBack(1);
	list1.addBack(4);
	list1.addBack(8);
	list1.addBack(16);
	list1.addBack(16);
	list1.addBack(24);

	list1.display();
	list1.removeDuplicates();
	list1.reverseRecursive(list1.head, NULL);
	list1.reverseLinks();
	list1.display();

	return 0;
}
