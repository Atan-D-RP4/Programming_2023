// Calculate Fibonacci Numbers
// Public Domain
// https://creativecommons.org/publicdomain/zero/1.0/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <gmp.h>
#include <time.h>
#include <regex.h>

#include <immintrin.h>

long limit, i = 0;

int main(int argc, char *argv[])
{

	// Create regex for url validation:
	regex_t regex;
	int reti;
	char msgbuf[100];

	reti = regcomp(&regex, "^[0-9]+$", 0);
	if (reti) {
		fprintf(stderr, "Could not compile regex\n");
		exit(1);
	}

	// Execute regex:
	reti = regexec(&regex, argv[1], 0, NULL, 0);
	if (!reti) {
		puts("Match");
	} else if (reti == REG_NOMATCH) {
		puts("No match");
	} else {
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		exit(1);
	}

	// Get User Input
	if (argc != 2)
	{
		printf("Improper input. Exiting.\n");
		return -1;
	}

	limit = strtol(argv[1], NULL, 10);

	// Setup GMP
	mpz_t a, b, c;
	mpz_init_set_ui(a, 1);
	mpz_init_set_ui(b, 0);
	mpz_init(c);

	// Start timing
	clock_t start_time = clock();

	for (i = 0; i < limit; i++)
	{
		// Perform the Fibonacci Calculation
		mpz_add(c, a, b);
		mpz_set(a, b);
		mpz_set(b, c);
	}

	// End timing
	clock_t end_time = clock();

	// Print the results to stdout
	printf("Fibonacci Number %ld: ", i);
	mpz_out_str(stdout, 10, b);
	printf("\n");

	// Cleanup
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);

	// Print time taaken
	double time_taken = ((double) end_time - start_time)  / CLOCKS_PER_SEC;
	printf("Calculation Time: %f seconds\n", time_taken);


	return 0;
}
