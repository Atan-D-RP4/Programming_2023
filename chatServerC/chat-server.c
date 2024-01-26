#include <arpa/inet.h>
#include <errno.h>
#include <poll.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int sockFD = socket(AF_INET, SOCK_STREAM, 0); // Creating an endpoint for Comms.
    if (sockFD == -1)
    {
        fprintf(stderr, "Socket Failed! errorno: %d (%s)\n", errno, strerror(errno));
        return 1;
    }

    struct sockaddr_in address = {
        AF_INET,
        htons(9999),
        0
    };

    if (bind(sockFD, (struct sockaddr *)&address, sizeof(address))) // Binding the socket to the address.
    {
        fprintf(stderr, "Binding Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return 1;
    }
        
    if (listen(sockFD, 10) == -1); // Listening for incoming connections.
    {   
        fprintf(stderr, "Listen Failed! errorno: %d (%s)\n", errno, strerror(errno));
    }
    
    int clientFD = accept(sockFD, NULL, NULL);
    if (clientFD == -1)
    {
        fprintf(stderr, "Client Accepting Failed! errorno: %d (%s)\n", errno, strerror(errno));
        close(sockFD);
        return 1;
    }

    struct pollfd fds[2] = {
        {
            0, // stdin
            POLLIN,
            0 // return events
        },
        {
            clientFD,
            POLLIN,
            0
        }
    };


    for (;;)
    {
        char buffer[256] = { 0 };
        poll(fds, 2, -1);
        if (fds[0].revents & POLLIN)
        {
            // read(0, buffer, sizeof(buffer));
            if (fgets(buffer, sizeof(buffer), stdin) == NULL)
                break;
            ssize_t bytesSent = send(clientFD, buffer, sizeof(buffer), 0);
            if (bytesSent == -1)
            {
                fprintf(stderr, "Sending Failed! errorno: %d (%s)\n", errno, strerror(errno));
                break;
            }
        }
        else if (fds[1].revents & POLLIN)
        {
            // if (recv(clientFD, buffer, sizeof(buffer), 0) == 0)
            //    return 0;
            ssize_t bytesReceived = recv(clientFD, buffer, sizeof(buffer), 0);
            if (bytesReceived <= 0)
            {
                (bytesReceived == 0 ? fprintf(stderr, "Client Disconnected!\n") : fprintf(stderr, "Client Receiving Failed! errorno: %d (%s)\n", errno, strerror(errno)));
                break;
            }

            buffer[bytesReceived] = '\0';
            printf("%s\n", buffer);
        }
    }
    close(clientFD);
    close(sockFD);
    return 0;
}