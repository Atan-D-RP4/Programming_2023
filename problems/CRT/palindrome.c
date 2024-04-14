#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_palindrome(int num);

int main(void)
{
    printf("Enter Number: ");
    int num;
    scanf("%d", &num);

   if (is_palindrome(num))
       return -1;

    int num_len = 0;
    for (int i = num; i > 0; i /= 10)
        num_len++;


}

int is_palindrome(int num)
{
    int rev = 0, rem = 0;


    printf("%d\n", rev);
    return (rev == num);
}

