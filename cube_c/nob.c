#define NOB_IMPLEMENTATION
#include "nob.h"

#define ARGPARSE_IMPLEMENTATION
#include "argparse.h"

#include <stdio.h>

int main(int argc, const char **argv) {
	NOB_GO_REBUILD_URSELF(argc, argv);

	struct argparse argparse;
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_GROUP("Basic options"),
		OPT_END(),
	};
	argparse_init(&argparse, options, NULL, 0);
	argc = argparse_parse(&argparse, argc, argv);

	return 0;
}
