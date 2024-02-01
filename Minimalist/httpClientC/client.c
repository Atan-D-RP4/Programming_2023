#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int sockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFD == -1)
    {
        fprintf(stderr, "Socket Failed! errorno: %d (%s)\n", errno, strerror(errno));
        return 1;
    }

    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(443),                 // 443 is the default TCP/UDP port
        .sin_addr.s_addr = inet_addr("8.8.8.8") // Public IP address to dns.google.com
                                                // .sin_addr.s_addr = inet_addr("142.250.70.46") // Public IP address to google.com
    };

    if (connect(sockFD, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        fprintf(stderr, "Connecting Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return 1;
    }

    SSL_CTX *ctx = SSL_CTX_new(TLS_method());
    if (ctx == NULL)
    {
        fprintf(stderr, "SSL_CTX_new Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return 1;
    }

    SSL *ssl = SSL_new(ctx);
    if (ssl == NULL)
    {
        fprintf(stderr, "SSL_new Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return 1;
    }

    if (SSL_set_fd(ssl, sockFD) != 1)
    {
        fprintf(stderr, "SSL_set_fd Failed! errorno: %d (%s)\n", errno, strerror(errno));
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockFD);
        return 1;
    }

    if (SSL_connect(ssl) != 1)
    {
        fprintf(stderr, "SSL_connect Failed! errorno: %d (%s)\n", errno, strerror(errno));
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockFD);
        return 1;
    }

    char *request = "GET /\r\n\r\n";
    if (SSL_write(ssl, request, strlen(request)) <= 0)
    {
        fprintf(stderr, "SSL_write Failed! errorno: %d (%s)\n", errno, strerror(errno));
        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockFD);
        return 1;
    }

    char buffer[1024] = {0};
    if (SSL_read(ssl, buffer, sizeof(buffer) - 1) <= 0)
    {
        fprintf(stderr, "SSL_read Failed! errorno: %d (%s)\n", errno, strerror(errno));
        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sockFD);
        return 1;
    }
    buffer[sizeof(buffer) - 1] = '\0';

    printf("Request: \n%s\n", buffer);

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sockFD);

    return 0;
}
