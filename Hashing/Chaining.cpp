#include <iostream>

using namespace std;

class Node {
	public:
		Node(int x) {
			data = x;
			next = NULL;
		}
		int data;
		Node *next;
};

class List {
	public:
		List() { head = NULL; }
		~List() { delete_list(head); }

		void insert(int key) {
			if (!head) {
				head = new Node(key);
				return ;
			}

			Node *p = head, *q = NULL;
			while (p && key > p->data) {
				q = p;
				p = p->next;
			}
			Node *new_node = new Node(key);
			if (q == NULL) {
				head = new_node;
				new_node->next = p;
			} else {
				new_node->next = q->next;
				q->next = new_node;
			}
		}

		int remove(int key) {
			if (!head) return -1;
			Node *p = head, *q = NULL;
			while (p && p->data != key) {
				q = p;
				p = p->next;
			}
			if (!p) return -1;
			if (!q)
				head = p->next;
			else
				q->next = p->next;
			int ret = p ? p->data : -1;
			delete p;
			return ret;
		}

		Node *search(int key) {
			for (Node *tmp = head; tmp; tmp = tmp->next) {
				if (tmp->data == key)
					return tmp;
			}
			return NULL;
		}

		static void delete_list(Node *node) {
			if (!node) return ;
			delete_list(node->next);
			delete node;
		}

		void display() {
			Node *node = head;
			while (node) {
				cout << node->data;
				if (node->next) cout << ", ";
				node = node->next;
			}
			cout << endl;
		}

		Node *head;
};

class Hash {
	public:
		Hash(int n) {
			stash = new List *[n];
			for (int i = 0; i < n; i++) stash[i] = NULL;
			size = n;
		}

		~Hash() {
			for (int i = 0; i < size; i++)
				if (stash[i]) delete stash[i];
			delete[] stash;
		}

		void insert(int key) {
			int hashed_value = hashing_function(key);
			if (!stash[hashed_value]) {
				stash[hashed_value] = new List;
				stash[hashed_value]->insert(key);
			} else {
				stash[hashed_value]->insert(key);
			}
		}

		Node *search(int key) {
			int hashed_value = hashing_function(key);
			return stash[hashed_value] ? stash[hashed_value]->search(key) : NULL;
		}

		int remove(int key) {
			int hashed_value = hashing_function(key);
			if (!stash[hashed_value])
				return -1;
			return stash[hashed_value]->remove(key);
		}

		Node *operator[](int key) {
			return search(key);
		}

		void display() {
			for (int i = 0; i < size; i++) {
				cout << i << ":  ";
				if (stash[i])
					stash[i]->display();
				else
					cout << endl;
			}
		}

	private:
		List **stash;
		int size;
		int hashing_function(int key) { return key % 10; }

};

int main() {
	Hash hm(10);

	hm.insert(4);
	hm.insert(9);
	hm.insert(13);
	hm.insert(3);
	hm.insert(10);
	hm.insert(5);
	hm.insert(25);

	hm.display();

	Node *to_find = hm[25];
	to_find ? cout << "Found: " << to_find->data << endl : cout << "Key not found" << endl;

	hm.remove(25);
	hm.remove(25);
	hm.display();
	return 0;
}
