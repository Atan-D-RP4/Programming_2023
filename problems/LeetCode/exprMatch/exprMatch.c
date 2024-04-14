#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Deals with like 308/356 test cases
bool isMatch(char* s, char* p) {
    if (strcmp(s,p) == 0)
        return true;
    else
    {
        int len_s = strlen(s);
        int len_p = strlen(p);
        int dp[len_s + 1][len_p + 1];
        for (int i = 0; i <= len_s; i++) {
            for (int j = 1; j <= len_p; j++)
                dp[i][j] = false;
        }
        dp[0][0] = true;

        for (int j = 0; j < len_p; ++j)
        {
            if (p[j] == '*' && dp[0][j - 1])
                dp[0][j + 1] = 1;
        }

        for (int i = 0; i < len_s; i++)
        {
            for (int j = 0; j < len_p; j++)
            {
                if (p[j] == '*')
                {
                    int repeat = i >= 0 && (p[j - 1] == '.' || s[i] == p[j - 1]) && dp[i][j + 1];
                    dp[i + 1][j + 1] = dp[i + 1][j - 1] || repeat;
                }
                else if (i >= 0 && (p[j] == s[i] || p[j] == '.'))
                    dp[i + 1][j + 1] = dp[i][j];
            }
        }

        return dp[len_s][len_p];
    }
}
*/

// Correct solution
bool isMatchHelper(char s, char p) {
    return (p == '.' || s == p);
}

bool isMatch(char* s, char* p) {
    int m = strlen(s);
    int n = strlen(p);

    // dp[i][j]: true if s[0..i) matches p[0..j)
    bool dp[m + 1][n + 1];
    memset(dp, false, sizeof(dp));
    dp[0][0] = true;

    for (int j = 0; j < n; ++j) {
        if (p[j] == '*' && dp[0][j - 1]) {
            dp[0][j + 1] = true;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (p[j] == '*') {
                bool noRepeat = dp[i + 1][j - 1];
                bool doRepeat = (i >= 0 && isMatchHelper(s[i], p[j - 1]) && dp[i][j + 1]);
                dp[i + 1][j + 1] = noRepeat || doRepeat;
            } else if (i >= 0 && isMatchHelper(s[i], p[j])) {
                dp[i + 1][j + 1] = dp[i][j];
            }
        }
    }

    return dp[m][n];
}

int main()
{
    // For Testing
    char a[] = {"mississippi"};
    char b[] = {"mis*is*p*."};
    if (isMatch(a, b))
        printf("True!\n");
    else
        printf("False!\n");
}
