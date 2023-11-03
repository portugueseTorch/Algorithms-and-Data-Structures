#include "Hash.hpp"

class Hash: public AHash {
	public:
		Hash(int n = 20): AHash(n) {}
		~Hash() { delete stash; }
	private:
		int hashing_function(int key) {
			return key % this->size;
		}

		int search(int key) {
			int hashed_value = hashing_function(key);
			if (stash[hashed_value] == -1) return -1;
			int i = 0;
			while (stash[(hashed_value + i) % size] != -1 && stash[(hashed_value + i) % size] != key)
				i++;
			return stash[(hashed_value + i) % size];
		}

		void resolve_collision(int key, int index) {
			int i = 0;
			while (stash[(index + i) % size] != -1)
				i++;
			stash[(index + i) % size] = key;
		}

		// Removal in linear probing is not advised, since it involves re-hashing
		void removal_method(int key, int index) {}
};

int main() {
	Hash linear(20);

	linear.insert(4);
	linear.insert(1);
	linear.insert(7);
	linear.insert(11);
	linear.insert(6);
	linear.insert(2);
	linear.insert(21);
	linear.insert(24);
	linear.insert(19);
	linear.insert(39);

	linear.display();

	cout << linear[21] << endl;
	return 0;
}
