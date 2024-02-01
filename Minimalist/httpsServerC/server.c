#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

#define MAX_CONNECTIONS 10

int main(int argc, char *argv[])
{
    int sockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFD == -1)
    {
        fprintf(stderr, "Socket Failed! errorno: %d (%s)\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY};

    if (bind(sockFD, (struct sockaddr *)&address, sizeof(address)))
    {
        fprintf(stderr, "Binding Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return EXIT_FAILURE;
    }

    if (listen(sockFD, MAX_CONNECTIONS) < 0)
        fprintf(stderr, "Listen Failed! errorno: %d (%s)\n", errno, strerror(errno));

    int clientFD = accept(sockFD, NULL, NULL);
    if (clientFD == -1)
    {
        fprintf(stderr, "Client Accepting Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return EXIT_FAILURE;
    }

    SSL_CTX *ctx = SSL_CTX_new(TLS_method());
    if (ctx == NULL)
    {
        fprintf(stderr, "SSL_CTX_new Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return EXIT_FAILURE;
    }

    SSL *ssl = SSL_new(ctx);
    if (ssl == NULL)
    {
        fprintf(stderr, "SSL_new Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return EXIT_FAILURE;
    }

    if (SSL_set_fd(ssl, sockFD) != 1)
    {
        fprintf(stderr, "SSL_set_fd Failed! errorno: %d (%s)\n", errno, strerror(errno));
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockFD);
        return EXIT_FAILURE;
    }

    if (SSL_connect(ssl) != 1)
    {
        fprintf(stderr, "SSL_connect Failed! errorno: %d (%s)\n", errno, strerror(errno));
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockFD);
        return EXIT_FAILURE;
    }

    SSL_use_certificate_chain_file(ssl, "filechain.pem");
    SSL_use_PrivateKey_file(ssl, "privateKey.pem", SSL_FILETYPE_PEM);
    SSL_accept(ssl);

    char buffer[1024] = {0};
    if (SSL_read(ssl, buffer, sizeof(buffer) - 1) <= 0)
    {
        fprintf(stderr, "SSL_read Failed! errorno: %d (%s)\n", errno, strerror(errno));
        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockFD);
        return EXIT_FAILURE;
    }

    // GET /file ...
    char *file_request = buffer + 5;
    char response[1024] = {0};
    char *metadata = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    memcpy(response, metadata, strlen(metadata));

    if (strncmp(file_request, "index.html", 11) == 0)
    {
        FILE *fp1 = fopen("index.html", "r");
        fread(response, 1024 - strlen(metadata) - 1, sizeof(char), fp1);
        fclose(fp1);
    }
    else
    {
        char *error = "<h1>404 Not Found</h1>";
        memcpy(response + strlen(metadata), error, strlen(error));
    }

    SSL_write(ssl, response, strlen(response));

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(clientFD);
    close(sockFD);

    return EXIT_SUCCESS;
}
