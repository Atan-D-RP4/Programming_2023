// The Successful Implementation
// All Test Cases Passed

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int max (int num1, int num2)
{
    return ((num1 > num2) ? num1 : num2);
}

int longestSubstring(char* s)
{
    int maxLen = 0, start = 0;
    int longestSubStrStart = 0, charIndex[256] = { 0 };
    for (int i = 0; i < strlen(s); i++)
    {
        int chrNow = s[i];
        start = max(charIndex[chrNow], start);
        if (i - start + 1 > maxLen)
        {
            maxLen = i - start + 1;
            longestSubStrStart = start;
        }
        charIndex[chrNow] = i + 1;
    }

    char longestSubStr[maxLen + 1];
    for (int i = 0; i < maxLen; i++)
        longestSubStr[i] = s[longestSubStrStart + i];
    longestSubStr[maxLen] = '\0';
    printf("Longest Substring: %s\n", longestSubStr);
    return maxLen;
}

int main()
{
    string given = get_string("Enter String: ");
    printf("Length of Longest Substring: %d\n",longestSubstring(given));
    return 0;
}
