#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int sockFD = socket(AF_INET, SOCK_STREAM, 0); // Creating an endpoint for Comms.

    struct sockaddr_in address = {
        AF_INET,
        htons(9999),
        0
    };

    connect(sockFD, (struct sockaddr *)&address, sizeof(address));

    struct pollfd fds[2] = {
        {
            0, // stdin
            POLLIN,
            0 // return events
        },
        {
            sockFD,
            POLLIN,
            0
        }
    };

    char buffer[256] = { 0 };
    poll(fds, 2, -1);

    for (;;)
    {
        if (fds[0].revents & POLLIN)
        {
            // read(0, buffer, sizeof(buffer));
            if (fgets(buffer, sizeof(buffer), stdin) == NULL)
                break;
            send(sockFD, buffer, sizeof(buffer), 0);
        }
        else if (fds[1].revents & POLLIN)
        {
            if (recv(sockFD, buffer, sizeof(buffer), 0) <= 0)
                break;
            printf("%s\n", buffer);
        }
    }
    close(sockFD);
    return 0;
}