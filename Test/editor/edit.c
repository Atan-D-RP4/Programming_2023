#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void editLine(char *buffer, int currLine);

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "File Error: %d(%s)\n", errno, strerror(errno));
        return errno;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = malloc(fileSize + 1);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory Error: %d(%s)\n", errno, strerror(errno));
        fclose(file);
        return errno;
    }
    buffer[fileSize] = '\0';
    fread(buffer, fileSize, 1, file);
    fclose(file);
    buffer[fileSize] = '\0';

    int currLine = 0;
    printf("Contents: \n%s\n", buffer);
    scanf("%d", &currLine);

    editLine(buffer, currLine);

    file = fopen(argv[1], "w");
    if (file == NULL)
    {
        fprintf(stderr, "File Error: %d(%s)\n", errno, strerror(errno));
        free(buffer);
        return errno;
    }
    fprintf(file, "%s", buffer);

    fclose(file);
    free(buffer);
    return 0;
}


void editLine(char *buffer, int currLine)
{
    int lineCount = 0;
    char *lineStart = buffer;
    while (lineCount < currLine && *lineStart)
    {
        lineStart = strchr(lineStart, '\n');
        if (lineStart)
        {
            lineStart++;
            lineCount++;
        }
    }

    if (!*lineStart)
    {
        fprintf(stderr, "Invalid Line Number: %d(%s)\n", errno, strerror(errno));
        return;
    }

    char *lineEnd = strchr(lineStart, '\n');
    if (lineEnd)
    {
        char saved[1024] = { 0 };
        strcpy(saved, lineEnd);
        printf("Enter new text for line %d: ", currLine);
        scanf("%s", lineStart);  // Read new text
        lineStart[strlen(lineStart) - 1] = '\0';
        strcpy(lineStart + strlen(lineStart), saved);
    }
    else
        fprintf(stderr, "Invalid Line Number\n");
}
