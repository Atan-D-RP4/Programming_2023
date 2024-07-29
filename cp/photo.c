#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int solve() {
	int n; scanf("%d", &n);
	int arr[n];

	for (size_t i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	if (arr[0] < arr[n - 1]) {
		for (size_t i = 0; i < n - 1; i++) {
			if (!(arr[i] <= arr[i + 1])) {
				printf("N %ld\n", i);
				return 0;
			}
		}
		printf("L\n");
	} else {
		for (size_t i = 0; i < n - 1; i++) {
			if (!(arr[i] >= arr[i + 1])) {
				printf("N\n");
				return 0;
			}
		}
		printf("R\n");
	}
}

int main(int argc, char *argv[]) {
	int t; scanf("%d", &t);

	while (t--) {
		solve();
	}
}
