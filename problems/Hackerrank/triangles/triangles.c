#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

void swap(float* a, float* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_tr(triangle* a, triangle* b)
{
    struct triangle temp = *a;
    *a = *b;
    *b = temp;
}

void sort_by_area(triangle* tr, int n)
{
	/**
	* Sort an array a of the length n
	*/

    float s[n];
    for (int i = 0; i < n; i++)
    {
        float p = (tr[i].a + tr[i].b + tr[i].c) / 2.0;
        s[i] = sqrtf(p * (p - tr[i].a) * (p - tr[i].b) * (p - tr[i].c));
    }

    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (s[j] < s[min])
                min = j;
        }

        if (min != i)
        {
            swap(&s[min], &s[i]);
            swap_tr(&tr[min], &tr[i]);
        }
    }
}

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}
