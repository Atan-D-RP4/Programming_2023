#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main (void)
{
    string strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "too hat"};
    string s = get_string("Search for: ");
    for(int i = 0; strings[i] != (void *)0; i++)
    {
        if(strcmp(strings[i], s) == 0)
        {
        printf("Found in strings[%d]\n", i);
        return 0;
        }
    }
    printf("Not found\n");
    return 1;
}