#include <cs50.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

unsigned int bit_sum(int a, int b)
{
    int result = a ^ b;
    int carry = (a & b) << 1;
    if (carry == 0)
        return result;
    else
        return bit_sum(carry, result);
}

int bit_product(int a, int b)
{
    int result = 0;
    while (b > 0)
    {
        if (b & 1)
            result += a;
        a = a << 1;
        b = b >> 1;
    }
    return result;
}

// Above are Optimization Functions for Arithemetic Operations

bool isHappy(int n) // Fully Working Solution :: All Test Cases Passed
{
    if (n == 1)
        return true;
    else if (n <= 6 && n > 1)
        return false;

    int sum = 0;
    do
    {
        sum = bit_sum(sum, bit_product((n % 10), (n % 10)));
        n /= 10;
    }
    while (n > 0);

    if (sum == 1)
        return true;
    else
        return isHappy(sum);
}

int main(void)
{
    int n = get_int("Number: ");
    if (isHappy(n))
        printf("True\n");
    else
        printf("False\n");
    return 0;
}
