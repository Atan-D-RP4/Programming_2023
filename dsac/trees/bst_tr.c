#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    struct node* left;
    struct node* right;
    int data;
}
node;

void traverseIn(node* root)
{
    if (root == NULL)
        return;
    traverseIn(root->left);
    printf("%d ", root->data);
    traverseIn(root->right);
}

void traversePre(node* root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    traversePre(root->left);
    traversePre(root->right);
}

void traversePost(node* root)
{
    if (root == NULL)
        return;
    traversePost(root->left);
    traversePost(root->right);
    printf("%d ", root->data);
}

node* insert(node* root, int data)
{
    if (root == NULL)
    {
        node* new = (node*)malloc(sizeof(node));
        if (new == NULL)
        {
            printf("Failed to Allocate Memory\n");
            // delete_all(root);
            exit(-1);
        }
        new->data = data;
        new->left = new->right = NULL;
        return new;
    }

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

node* constructBST(int data[], int size)
{
    node* root = NULL;
    for (int i = 0; i < size; i++)
        root = insert(root, data[i]);
    return root;
}

node* search(node* root, int key)
{
    if (root == NULL || root->data == key)
        return root;
    if (root->data < key)
        return search(root->right, key);
    return search(root->left, key);
}

void search1(node* root, int key)
{
    if (root->left == NULL && root->right == NULL)
    {
        if (key == root->data)
            printf("Found In Tree\n");
        else
            printf("Not In Tree\n");
        return;
    }

    if (key < root->data)
        search(root->left, key);
    else
        search(root->right, key);
    return;
}

node* delete(node* root, int key)
{
    if (root == NULL)
    {
        printf("Empty Tree\n");
        return root;
    }
    if (root->data > key)
    {
        root->left = delete(root->left, key);
        return root;
    }
    else if (root->data < key)
    {
        root->right = delete(root->right, key);
        return root;
    }

    if (root->left == NULL)
    {
        node* tmp = root->right;
        free(root); root = NULL;
        return tmp;
    }
    else if (root->right == NULL)
    {
        node* tmp = root->left;
        free(root); root = NULL;
        return tmp;
    }
    else
    {
        node* succPar = root, *succ = root->right;
        while (succ->left != NULL)
        {
            succPar = succ;
            succ = succ->left;
        }
        if (succPar != root)
            succPar->left = succ->right;
        else
            succPar->right = succ->right;
        root->data = succ->data;
        free(succ); succ = NULL;
        return root;
    }

}

int main(int argc, char* argv[])
{
    printf("Enter No.of Elements in the Tree: ");
    int n; scanf("%d", &n);
    int arr[n];
    printf("Enter BST In-Order: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    node* newTree = constructBST(arr, n);

    printf("Tree Operations: \n");
    printf("1. Traverse InOrder\n2. Traverse PreOrder\n3. Traverse PostOrder\n");
    printf("4. Insert\n5. Delete\n6. Search\n");
    printf("Press X to exit\n");

    while(true)
    {
        printf("[1/2/3/4/5]: ");
        int key = 0;char choice = 0;
        scanf(" %c", &choice);
        switch (choice)
        {
            case '1':
                traverseIn(newTree);
                printf("\n");
                break;
            case '2':
                traversePre(newTree);
                printf("\n");
                break;
            case '3':
                traversePost(newTree);
                printf("\n");
                break;
            case '4':
                printf("Insert: "); scanf("%d", &key);
                newTree = insert(newTree, key);
                break;
            case '5':
                printf("Delete: "); scanf("%d", &key);
                newTree = delete(newTree, key);
                break;
            case '6':
                printf("Search For: "); scanf("%d", &key);
                search1(newTree, key);
                break;
            case ('X' | 'x'):
                // delete_all(newTree);
                exit(0);
            default:
                printf("Enter Valid Choice!\n");
        }
    }
}
