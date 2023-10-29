#include "Hash.hpp"

class Hash: public AHash {
	public:
		Hash(int n = 20): AHash(n) {}
	private:
		int hashing_function(int key) {
			return key % this->size;
		}

		int search(int key) {
			int hashed_value = hashing_function(key);
			if (stash[hashed_value] == -1) return -1;
			for (int i = 0; stash[hashed_value] != -1 && stash[hashed_value] != key; i++) {
				hashed_value = (hashed_value + i) % size;
			}
			return stash[hashed_value];
		}

		void resolve_collision(int key, int index) {
			for (; stash[index] != -1;)
				index = (index + 1) % size;
			stash[index] = key;
		}

		void removal_method(int key, int index) {}
};

int main() {
	Hash linear(20);

	linear.insert(4);
	linear.insert(1);
	linear.insert(7);
	linear.insert(11);
	linear.insert(21);
	linear.insert(6);
	linear.insert(2);
	linear.insert(24);
	linear.insert(44);

	linear.display();

	cout << linear[5] << endl;
	return 0;
}
