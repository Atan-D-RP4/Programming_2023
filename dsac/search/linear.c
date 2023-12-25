#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int numbers[] = {20, 50, 200, 100, 1, 500};
    int n = get_int("Search for: ");
    for(int i = 0; numbers[i] != '\0'; i++)
    {
        if(numbers[i] == n)
        {
        printf("Found in numbers[%d]\n", i);
        return 0;
        }
    }
    printf("Not found\n");
    return 1;
}