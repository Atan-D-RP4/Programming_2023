// Implements Input of Polynomial Expressions
// And Their Addition and Multiplication Operations

// Finished (Logical)
// Final Testing Pending -- All test cleared

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct term
{
    float coeff;
    int xpo;
    struct term* link;
}term;

term* get_poly(void);
term* insert_trm(term* start, float coeff, int xpo);
void display(term* poly);
term* poly_add(term* poly1, term* poly2);
term* poly_product(term* poly1, term* poly2);
void delete_all(term* start);

int main(void)
{
    printf("Enter First Polynomial: \n");
    term* poly1 = get_poly();
    printf("Enter Second Polynomial: \n");
    term* poly2 = get_poly();

    printf("Sum of \n");
    display(poly1); display(poly2);
    printf("is: ");
    term* poly_sum = poly_add(poly1, poly2);
    display(poly_sum);

    printf("Product of: \n");
    display(poly1); display(poly2);
    printf("is ");
    term* poly_mult = poly_product(poly1, poly2);
    display(poly_mult);

    delete_all(poly1);
    delete_all(poly2);
    delete_all(poly_sum);
    delete_all(poly_mult);

    return 0;
}

term* get_poly(void)
{
    term* new = NULL;
    int n, xpo;
    float coeff;
    printf("Enter No.of Terms: "); scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        printf("Enter Co-efficient of Term %d: ", i);
        scanf("%f", &coeff);
        printf("Enter Exponent of Term %d: ", i);
        scanf("%d", &xpo);
        new = insert_trm(new, coeff, xpo);
    }
    return new;
}

term* insert_trm(term* start, float coeff, int xpo)
{
    term* new = (term*)malloc(sizeof(term));
    if (new == NULL)
    {
        printf("Failed To Allocate Memory!\n");
        delete_all(start);
    }
    new->coeff = coeff;
    new->xpo = xpo;
    new->link = NULL;

    term* cursor;

    if (start == NULL || xpo > start->xpo)
    {
        new->link = start;
        start = new;
    }
    else
    {
        for (cursor = start; cursor->link != NULL && cursor->link->xpo > xpo; cursor = cursor->link);
        if (cursor->link->xpo == xpo)
        {
            cursor->link->coeff += new->coeff;
            free(new);
            return start;
        }
        new->link = cursor->link;
        cursor->link = new;
    }

    return start;
}


term* poly_add(term* poly1, term* poly2)
{
    if (poly1 == NULL || poly2 == NULL)
    {
        printf("Invalid Polynomials\n");
        return NULL;
    }

    term* sum = NULL;
    term* p1 = poly1;
    term* p2 = poly2;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->xpo > p2->xpo)
        {
            sum = insert_trm(sum, p1->coeff, p1->xpo);
            p1 = p1->link;
        }
        else if (p1->xpo < p2->xpo)
        {
            sum = insert_trm(sum, p2->coeff, p2->xpo);
            p2 = p2->link;
        }
        else if(p1->xpo == p2->xpo)
        {
            sum = insert_trm(sum, (p1->coeff + p2->coeff), p1->xpo);
            p2 = p2->link;
            p1 = p1->link;
        }
    }

    for (; p1 != NULL; p1 = p1->link)
        sum = insert_trm(sum, p1->coeff, p1->xpo);

    for (; p2 != NULL; p2 = p2->link)
        sum = insert_trm(sum, p2->coeff, p2->xpo);

    return sum;
}

term* poly_product(term* poly1, term* poly2)
{
    if (poly1 == NULL || poly2 == NULL)
    {
        printf("Invalid Polynomials\n");
        return NULL;
    }

    term* product = NULL;
    term* p1 = poly1;

    while (p1 != NULL)
    {
        term* p2 = poly2;
        while (p2 != NULL)
        {
            product = insert_trm(product, (p1->coeff * p2->coeff), (p1->xpo + p2->xpo));
            p2 = p2->link;
        }
        p1 = p1->link;
    }

    return product;
}

void display(term* poly)
{
    if (poly == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    for (term* crsr = poly; ; crsr = crsr->link)
    {
        if (crsr->link == NULL)
        {
            printf("(%.0fx^%d)", crsr->coeff, crsr->xpo);
            break;
        }
        printf("(%.0fx^%d) + ", crsr->coeff, crsr->xpo);
    }
    printf("\n");
}

void delete_all(term* start)
{
    if (start == NULL)
		return;
    term* to_del = NULL;
    for (term* cursor = start; cursor != NULL; )
    {
        to_del = cursor;
        cursor = cursor->link;
        free(to_del);
    }
}
