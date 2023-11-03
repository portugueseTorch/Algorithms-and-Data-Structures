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
			while (stash[(hashed_value + i * i) % size] != -1 && stash[(hashed_value + i * i) % size] != key)
				i++;
			return stash[(hashed_value + i * i) % size];
		}

		void resolve_collision(int key, int index) {
			int i = 0;
			while (stash[(index + i * i) % size] != -1)
				i++;
			stash[(index + i * i) % size] = key;
		}

		void removal_method(int key, int index) {}
};

int main() {
	Hash ht(20);

	ht.insert(4);
	ht.insert(14);

	ht.display();

	ht.insert(24);
	ht.display();

	cout << ht[24] << endl;
	return 0;
}
