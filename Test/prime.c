#include  <stdio.h>
int main(void)
{
    for(int i = 1; i <= 20; i++)
    {
        int a = 0;
        for(int j = 1; j <= i; j++)
        {
            if(i % j == 0)
            {
                a++;
            }
        }
        if(a == 2)
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}