// The Successful Implementation
// All Test Cases Passed

#include <cs50.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int64_t myAtoi0(char *s)
{
    int64_t num = 0;
    int c, signs = 1;
    bool negative = 0;
    while ((c = *s++))
    {
        if (c == ' ' || c == '0')
            continue;
        if (c == '-')
        {
            negative = true;
            signs--;
            continue;
        }
        else if (c == '+')
        {
            signs--;
            continue;
        }
        if (signs < 0)
            return num;
        if (isalpha(c) || c == '.')
        {
            if (num > 0)
                return num;
            return 0;
        }
        if (isdigit(c))
        {
            if (num == 0)
                num = c - 48;
            else
            {
                num = (10 * num) + (c - 48);
            }
        }
    }

    num = (num ^ -negative) + negative;

    if (num >= INT32_MIN && num <= INT32_MAX)
    {
        if (num == INT32_MAX - 1)
            return INT32_MAX;
        return num;
    }
    else
    {
        if (negative)
            num = INT32_MIN;
        else
            num = INT32_MAX;
    }
    return num;
}

int64_t myAtoi1(char *s) // First Fully Working Solution Function
{
    int64_t num = 0;
    int c, signs = 1, digits = 0;
    bool negative = 0;
    while ((c = *s++))
    {
        if (c == ' ')
        {
            if (signs <= 0 || digits > 0)
                return (negative ? -num : num);
            continue;
        }
        if (!isdigit(c) || c == '.')
        {
            if (c == '-' || c == '+')
            {
                signs--;
                if (digits > 0 || signs != 0)
                {
                    if (signs <= 0)
                        return (negative ? -num : num);
                    return 0;
                }
                negative = (c == '-');
                continue;
            }
            return (negative ? -num : num);
        }
        if (isdigit(c))
        {
            digits++;
            num = (10 * num) + (c - '0');
            if (num > INT32_MAX)
                return (negative ? INT32_MIN : INT32_MAX);
        }
    }

    return (negative ? -num : num);
}

int64_t myAtoi(char *s) // The Least Ugly Fully Working Solution Function
{
    int64_t num = 0;
    int c;
    int signs = 1;
    int digits = 0;
    bool negative = false;

    while ((c = *s++))
    {
        if (c == ' ')
        {
            if (signs <= 0 || digits > 0)
                return (negative ? -num : num);
            continue;
        }

        if (!isdigit(c) || c == '.')
        {
            if (c == '-' || c == '+')
            {
                signs--;
                if (digits > 0 || signs != 0)
                {
                    return (signs <= 0) ? (negative ? -num : num) : 0;
                }
                negative = (c == '-');
                continue;
            }
            return (negative ? -num : num);
        }

        if (isdigit(c))
        {
            digits++;
            num = (10 * num) + (c - '0');
            if (num > INT32_MAX)
            {
                return (negative ? INT32_MIN : INT32_MAX);
            }
        }
    }

    return (negative ? -num : num);
}

int main(void)
{
    string s = get_string("Number: ");
    int num = myAtoi(s);
    printf("%d\n", num);
}
