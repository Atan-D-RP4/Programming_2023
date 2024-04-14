#include <stdio.h>

int main() {
	
	int n = 10;

	for (int i = n / 2; i < n; i += 2) {
		for (int j = 1; j < n - i; j += 2) {
			printf(" ");
		}

		for (int j = 1; j <= i; j++) {
			printf("*");
		}

		for (int j = 1; j <= n - i; j++) {
			printf(" ");
		}

		for (int j = 1; j <= i; j++) {
			printf("*");
		}

		printf("\n");
	}

	for (int i = n; i > 0; i--) {
		for (int j = 0; j < n - i; j++) {
			printf(" ");
		}

		for (int j = 1; j < (i * 2); j++) {
			printf("*");
		}

		printf("\n");
	}
}
