#define _GNU_SOURCE
#include <error.h>
#include <errno.h>

#include "toralizer.h"

/*
 * ./toralize 1.2.3.4 80
 */

int connect(int fd, const struct sockaddr *addr, socklen_t len) {

	// Get the original connect function
	int (*connect_ptr)(int, const struct sockaddr *, socklen_t);
	connect_ptr = dlsym(RTLD_NEXT, "connect");

	Proxy_Request *req = create_request((struct sockaddr_in *) addr);
	Proxy_Response *res = NULL;
	char buf[RES_SIZE];

	fprintf(stderr, "Connecting to %s:%d\n", inet_ntoa(((struct sockaddr_in *) addr)->sin_addr),
			ntohs(((struct sockaddr_in *) addr)->sin_port));

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		fprintf(stderr, "Failed to create socket\n");
		return EXIT_FAILURE;
	} else {
		printf("Socket created\n");
	}

	// Setting REUSE_PORT ensures that we don't run into 'Address already in use' errors
	int reuse = 1;
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
		fprintf(stderr, "SO_REUSEPORT failed: %s \n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		printf("SO_REUSEPORT set\n");
	}

	struct sockaddr_in sock = {
		.sin_family = AF_INET,
		.sin_port = htons(PROXY_PORT),
		.sin_addr.s_addr = inet_addr(PROXY_IP)
	};

	if (connect_ptr(sock_fd, (struct sockaddr *) &sock, sizeof(sock)) < 0) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		fprintf(stderr, "Failed to connect to proxy\n");
		return EXIT_FAILURE;
	} else {
		fprintf(stderr, "Connected to proxy\n");
	}

	memset(buf, 0, RES_SIZE);

	write(sock_fd, req, REQ_SIZE);
	if (read(sock_fd, buf, RES_SIZE) < 1) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		fprintf(stderr, "Failed to read response\n");
		free(req);
		if (close(sock_fd) < 0) {
			fprintf(stderr, "Error: %s\n", strerror(errno));
			fprintf(stderr, "Failed to close socket\n");
		}
		return EXIT_FAILURE;
	} else {
		fprintf(stderr, "Response read\n");
	}

	int success = 0;
	res = (Proxy_Response *) buf;
	success = res->cmd == 90 ? 1 : 0;
	if (!success) {
		fprintf(stderr, "Unable to Traverse Proxy\n");
		fprintf(stderr, "Error Code: %d\n", res->cmd);

		free(req);
		if (close(sock_fd) < 0) {
			fprintf(stderr, "Error: %s\n", strerror(errno));
			fprintf(stderr, "Failed to close socket\n");
		}
		return EXIT_FAILURE;
	} else {
		fprintf(stderr, "Successfully Connected through Proxy to"
				" %s:%d\n", inet_ntoa(((struct sockaddr_in *) addr)->sin_addr),
				ntohs(((struct sockaddr_in *) addr)->sin_port));
		fprintf(stderr, "Response: \n");
		fprintf(stderr, "Version: %d\n", res->ver);
		fprintf(stderr, "Command: %d\n", res->cmd);
	}
	dup2(sock_fd, fd);

	free(req);
	return EXIT_SUCCESS;
}

Proxy_Request *create_request(const struct sockaddr_in *addr) {
	Proxy_Request *req = calloc(1, REQ_SIZE);

	req->ver = 4;
	req->cmd = 1;
	req->dst_ip = addr->sin_addr.s_addr;
	req->dst_port = addr->sin_port;
	strncpy((char* ) req->username, USERNAME, 8);

	return req;
}
