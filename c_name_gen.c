#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *VOWELS = "aeiou";
const char *CONSONANTS = "bcdfghjklmnpqrstvwxyz";

#define rand_vowel() VOWELS[rand() % strlen(VOWELS)]
#define rand_consonant() CONSONANTS[rand() % strlen(CONSONANTS)]

const char *MY_PICKS[] = {

};

void rand_syl() {
	switch (rand() % 5) {
	case 0: printf("%c", rand_vowel()); break;
	case 1: printf("%c%c", rand_consonant(), rand_vowel()); break;
	case 2: printf("%c%c%c", rand_vowel(), rand_consonant(), rand_vowel()); break;
	case 3: printf("%c%c%c", rand_consonant(), rand_vowel(), rand_vowel()); break;
	case 4: printf("%c%c%c", rand_consonant(), rand_vowel(), rand_consonant()); break;
	}
}

void rand_word(int N, int syllabals) {
	for (size_t j = 0; j < N; ++j) {
		for (size_t i = 0; i < (2 + rand() % (syllabals - 2)); ++i) {
			rand_syl();
		}
		printf("\n");
	}
}

void mutate_word() {}

// Words:
// <syl> ::= <vowel> | <consonant><vowel> | <vowel><consonant><vowel> |
// <consonant><vowel><vowel> | <consonant><vowel><consonant> <word> ::= <syl> |
// <syl><syl> | <syl><syl><syl> | <syl><syl><syl><syl> |
// <syl><syl><syl><syl><syl>

int main() {
	printf("Hello, World!\n");
	srand(time(NULL));

	int N = 10;
	int syllabals = 5;

	rand_word(N, syllabals);

	return 0;
}
