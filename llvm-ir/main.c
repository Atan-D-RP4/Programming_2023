#include <stddef.h>
#include <stdio.h>

int main(void) {

	for (size_t i = 0; i < 10; i++) {
		printf("%zu\n", i);
	}
	printf("Hello, World!\n");
	return 0;
}
