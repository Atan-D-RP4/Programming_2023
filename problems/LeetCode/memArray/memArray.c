// The Successful Implementation
// All Test Cases Passed


#include <stdio.h>
#include <stdlib.h>

/*
 * This stores the total number of books in each shelf.
 */
int *total_number_of_books; // books[]

/*
 * This stores the total number of pages in each book of each shelf.
 * The rows represent the shelves and the columns represent the books.
 */
int **total_number_of_pages; // pages[][]

int main()
{
    int total_number_of_shelves;
    int total_number_of_queries;

    scanf("%d", &total_number_of_shelves);
    scanf("%d", &total_number_of_queries);

    total_number_of_books = (int*)malloc(total_number_of_shelves * sizeof(int));

    // Allocate memory for total_number_of_pages array
    total_number_of_pages = (int**)malloc(total_number_of_shelves * sizeof(int*));

    for (int i = 0; i < total_number_of_shelves; i++)
    {
        total_number_of_books[i] = 0; // Initialize the book count to 0 for each shelf
        total_number_of_pages[i] = NULL; // Initialize the pages array to NULL for each shelf
    }

    while (total_number_of_queries--)
    {
        int type_of_query;
        scanf("%d", &type_of_query);

        if (type_of_query == 1)
        {
            /*
             * Process the query of first type here.
             */
            int x, y;
            scanf("%d %d", &x, &y);

            // Check if the shelf has no books yet
            if (total_number_of_books[x] == 0)
            {
                // Allocate memory for one book on the shelf
                total_number_of_pages[x] = (int*)malloc(sizeof(int));
                // Initialize the book's page count to 0
                *total_number_of_pages[x] = 0;
            }

            // Update the total number of books on the shelf
            total_number_of_books[x]++;

            // Resize the array to accommodate the new book
            total_number_of_pages[x] = (int*)realloc(total_number_of_pages[x], total_number_of_books[x] * sizeof(int));

            // Update the total number of pages for the new book
            total_number_of_pages[x][total_number_of_books[x] - 1] = y;

        }
        else if (type_of_query == 2)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%d\n", *(*(total_number_of_pages + x) + y));
        }
        else
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", *(total_number_of_books + x));
        }
    }

    if (total_number_of_books)
    {
        free(total_number_of_books);
    }

    for (int i = 0; i < total_number_of_shelves; i++)
    {
        if (*(total_number_of_pages + i))
        {
            free(*(total_number_of_pages + i));
        }
    }

    if (total_number_of_pages)
    {
        free(total_number_of_pages);
    }

    return 0;
}
