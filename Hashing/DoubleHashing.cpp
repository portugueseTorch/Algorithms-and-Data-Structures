#include "Hash.hpp"
#include <math.h>

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

		int prime(int n) {
			if (n & 1)
				n -= 2;
			else
				n--;
		
			int i, j;
			for (i = n; i >= 2; i -= 2) {
				if (i % 2 == 0)
					continue;
				for (j = 3; j <= sqrt(i); j += 2) {
					if (i % j == 0)
						break;
				}
				if (j > sqrt(i))
					return i;
			}
			return 2;
		}

		void resolve_collision(int key, int index) {
			int i = 0;
			int dh = double_hash(key);
			while (stash[(index + i * dh) % size] != -1)
				i++;
			stash[(index + i * dh) % size] = key;
		}

		int double_hash(int key) {
			int nearest_prime = prime(size);
			return nearest_prime - (key % nearest_prime);
		}

		void removal_method(int key, int index) {}
};

int main() {
	Hash hm(10);

	hm.insert(5);
	hm.insert(25);
	hm.insert(15);
	hm.insert(35);
	hm.insert(95);

	hm.display();

	return 0;
}
