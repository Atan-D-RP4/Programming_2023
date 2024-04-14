#include <stdio.h>

int main(void)
{
	// your code goes here
	int cases, n, count = 0;
	scanf("%d", &cases);

	while(cases--)
	{
	    scanf("%d", &n);
    	char logicians[n];
    	scanf("%s", logicians);

    	for (int i = 0; i < n; i++)
    	{
    	    if (logicians[i] == '0')
                printf("NO\n");
            else
            {
                int flag = 0;
                for (int j = 0; j < i; j++)
                {
                    if (logicians[j] == '0')
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0 && i == n - 1)
                    printf("YES\n");
                else if (flag == 1)
                    printf("NO\n");
                else
                    printf("IDK\n");
            }
        }
	}
	return 0;
}

