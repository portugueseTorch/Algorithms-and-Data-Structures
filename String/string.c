#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void to_lower(char *str) {
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] >= 65 && str[i] <= 90) {
			str[i] += 32;
		}
	}
}

void find_duplicates(char *str) {
	int hash[26] = {0};
	to_lower(str);

	for (int i = 0; i < strlen(str); i++)
		hash[str[i] - 97]++;

	for (int i = 0; i < 26; i++) {
		if (hash[i] != 0) {
			printf("Character %c appears %d times\n", i + 97, hash[i]);
		}
	}
}

void bit_duplicates(char *str) {
	int hash = 0, tmp;
	to_lower(str);

	for (int i = 0; i < strlen(str); i++) {
		tmp = 1 << (str[i] - 97);
		if ((hash & tmp) != 0)
			printf("Character %c is repeated\n", str[i]);
		else
			hash |= tmp;
	}
}

bool is_anagram(char *str1, char *str2) {
	int hash[26] = {0};

	if (strlen(str1) != strlen(str2)) return false;

	to_lower(str1);
	to_lower(str2);

	for (int i = 0, j = 0; i < strlen(str1); i++, j++) {
		hash[str1[i] - 97]++;
		hash[str2[j] - 97]--;
	}

	for (int i = 0; i < 26; i++) {
		if (hash[i] != 0)
			return false;
	}
	return true;
}

void permutate(char str[], int k) {
	static int hash[10] = {0};
	static char result[10];
	int i;

	if (str[k] == '\0') {
		result[k] = '\0';
		printf("%s\n", result);
	} else {
		for (i = 0; str[i]; i++) {
			if (hash[i] == 0) {
				result[k] = str[i];
				hash[i] = 1;
				permutate(str, k + 1);
				hash[i] = 0;
			}
		}
	}
}

int main(int argc, char **argv) {
	if (argc != 2) return 1;

	permutate(argv[1], 0);
	return 0;
}