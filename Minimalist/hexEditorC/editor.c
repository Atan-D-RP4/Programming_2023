#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 16

void printHex(unsigned char *buffer, int bytesRead)
{
    for (int i = 0; i < bytesRead; i++)
    {
        if (i % 16 == 0)
            printf("LINE %3d: ", (i / 16) + 1);

        printf("%02X ", buffer[i]);

        if ((i + 1) % 16 == 0 || i == bytesRead - 1)
            printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp1 = fopen(argv[1], "r");
    if (fp1 == NULL)
    {
        fprintf(stderr, "File Error: %d(%s)\n", errno, strerror(errno));
        return errno;
    }

    fseek(fp1, 0, SEEK_END);
    long fp1Size = ftell(fp1);
    rewind(fp1);

    unsigned char *buffer = calloc(fp1Size + 1, sizeof(unsigned char));
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory Error: %d(%s)\n", errno, strerror(errno));
        fclose(fp1);
        return errno;
    }
    int bytesRead = fread(buffer, sizeof(char), fp1Size + 1, fp1);
    if (bytesRead < 0)
    {
        fprintf(stderr, "File read error: %d(%s)\n", errno, strerror(errno));
        free(buffer);
        fclose(fp1);
        return errno;
    }
    printHex(buffer, bytesRead);

    while (1)
    {
        char cmd;
        int line = 0;
        printf("Command:\np - print\ne - edit\ns - save\nq - quit\n");
        scanf(" %c", &cmd);
        if (cmd == 'q')
        {
            fclose(fp1);
            free(buffer);
            return EXIT_SUCCESS;
        }
        if (cmd == 'p')
        {
            printf("Location: ");
            scanf("%d", &line);
            if (line < 0 || line > bytesRead)
            {
                printf("Invalid location\n");
                continue;
            }
            printHex(buffer + line, LINE_SIZE);
            continue;
        }
        if (cmd == 'e')
        {
            getchar();
            printf("Location: ");
            scanf("%d", &line);
            if (line < 0 || line > bytesRead)
            {
                printf("Invalid location\n");
                continue;
            }
            scanf("%x", buffer + line);
        }
        if (cmd == 's')
            break;
        printf("\n");
    }

    fclose(fp1);
    FILE *fp2 = fopen("out.hex", "w");
    if (fp2 == NULL)
    {
        fprintf(stderr, "File Error: %d(%s)\n", errno, strerror(errno));
        free(buffer);
        return errno;
    }
    fwrite(buffer, sizeof(char), bytesRead, fp2);
    fclose(fp2);
    free(buffer);

    return EXIT_SUCCESS;
}