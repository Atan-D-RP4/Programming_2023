#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sendfile.h>
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

    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = htonl(INADDR_ANY),
    };

    if (bind(sockFD, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        fprintf(stderr, "Binding Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return 1;
    }

    if (listen(sockFD, 10) < 0)
    {
        fprintf(stderr, "Listen Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return 1;
    }

    int clientFD = accept(sockFD, NULL, NULL);
    if (clientFD == -1)
    {
        fprintf(stderr, "Client Accepting Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return 1;
    }

    char buffer[256] = {0};

    ssize_t bytesRead = recv(clientFD, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead < 0)
    {
        fprintf(stderr, "Reading Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(clientFD);
        close(sockFD);
        return 1;
    }

    // GET /file.html .....

    char *fileName = buffer + 5;
    char *fileNameEnd = strchr(fileName, ' ');
    if (fileNameEnd != NULL)
        *fileNameEnd = '\0';
    else
    {
        fprintf(stderr, "Invalid Request!\n");
        close(clientFD);
        close(sockFD);
        return 1;
    }

    int openedFD = open(fileName, O_RDONLY);
    if (openedFD == -1)
    {
        fprintf(stderr, "File Opening Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(clientFD);
        close(sockFD);
        return 1;
    }

    const char *httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    send(clientFD, httpHeader, strlen(httpHeader), 0);

    off_t offset = 0;
    ssize_t sentBytes = sendfile(clientFD, openedFD, &offset, sizeof(buffer) - 1);

    if (sentBytes == -1)
        fprintf(stderr, "Sending File Failed! errorno: %d (%s)\n", errno, strerror(errno));

    close(openedFD);
    close(clientFD);
    close(sockFD);

    return 0;
}