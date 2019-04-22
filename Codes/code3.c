/*
    Data Structures and Algorithms - Assignment 2 - Q1

    @author
    Student: Osman Araz
    Student NO: 16011020
    Delivery Date: 02.04.2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    A structure for binary search tree. It consists a value and addresses of its children.
*/
typedef struct TREE
{
    int value;
    struct TREE *left, *right;
} Node;

void controlFileCrash(FILE *);
int readValuesFromFile(FILE *, int *, int);
Node *arrayToBST(int *, int, int);
void printPreOrder(Node *root);
void printInOrder(Node *root);
void printPostOrder(Node *root);
int main()
{
    FILE *fi = fopen("input1.txt", "r");    // opening the file in reading mode
    controlFileCrash(fi);   // checking for file crashing

    int SIZE = 100;     // initial capacity of the array
    int *arr = (int *)malloc(100*sizeof(int));  // dynamically allocating the array
    int n = readValuesFromFile(fi, arr, SIZE);  // getting values of the array from the file
                                                // the function returns the size of the array
    fclose(fi);     // closing the file

    Node *root = arrayToBST(arr, 0, n-1);   // generating binary search tree from the array
                                            // the function returns the address of the root of the tree
    
    // printing the tree in forms of pre-order, in-order and post-order
    printf("Pre-Ordered BST: ");
    printPreOrder(root);
    printf("\nIn-Ordered BST: ");
    printInOrder(root);
    printf("\nPost-Ordered BST: ");
    printPostOrder(root);
    printf("\n");
    
    return 0;
}

/*
    A function which checks whether the file opened succesfully or not. 
    If not, then the program ends.
    @param *fi: The file pointer which consists values of the array.
*/
void controlFileCrash(FILE *fi)
{
    if (!fi)
    {
        printf("File could not be opened.\n");
        exit(1);
    }
}

/*
    A function which storing values to an array from a file.
    @param *fi: The file pointer which consists values of the array.
    @param *arr: The array pointer which will be used to storing the values.
    @param SIZE: The capacity of the array, which can be increase in the function. 
    @return i: The number of elements in the generated array.
*/
int extendArray(int *, int);
int readValuesFromFile(FILE *fi, int *arr, int SIZE)
{
    int i = 0;              // the indice of the array
    char line[500];         // a temporary string to get line from the file
    fgets(line, 500, fi);   // getting the line from the file
    char *numbers;          // a string token to split string to integers
    
    // strtok() function splits the string of comma seperated integers to individual integers
    arr[i++] = atoi(strtok(line, ","));
    
    while (numbers = strtok(NULL, ","))
    {
        arr[i++] = atoi(numbers);

        if (i == SIZE)  // if indice of the array reaches to the capacity, then the capacity of the array increases
            SIZE = extendArray(arr, SIZE);
    }

    return i;   // returning the last indice of the array, which represents the size of the array
}

/*
    A function which extends the size of an array.
    @param *arr: The pointer of the array.
    @param SIZE: The size of the array.
    @return: The updated size of the array.
*/
int extendArray(int *arr, int SIZE)
{
    SIZE *= 2;
    arr = realloc(arr, SIZE*sizeof(int));
    
    return SIZE;
}

/*
    A function which recursively generates a binary search tree from a sorted array.
    @param *arr: The pointer of the array.
    @param left: The given left indice of the array.
    @param right: The given right indice of the array.
    @return: The address of the updated root of the tree.
*/
Node *createNode();
Node *arrayToBST(int *arr, int left, int right)
{
    // the recursion continues while the left indice is not greater than the right indice
    if (left > right)
        return NULL;
    
    int mid = (left+right)/2;
    Node *root = createNode();  // creating a tree node
    root -> value = arr[mid];   // the value of the node will be the value in the middle indice of the array
    root -> left = arrayToBST(arr, left, mid-1);    // same process for the left child of the node
    root -> right = arrayToBST(arr, mid+1, right);  // same process for the right child of the node

    return root; // returning the addres of the node
}

/*
    A function which creates a node for a binary tree.
    @return: the address of the created node.
*/
Node *createNode()
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (!newNode)   // if the node could not be created, then the program ends
        exit(1);

    // the left and right children of the node initializing as NULL
    newNode -> left = NULL;
    newNode -> right = NULL;

    return newNode;   // returning the address of the node
}

/*
    A function which prints the tree in form of pre-order.
    @param *root: The address of the root of the tree.
*/
void printPreOrder(Node *root)
{
    if (root)
    {
        printf("%d ", root -> value);
        printPreOrder(root -> left);
        printPreOrder(root -> right);
    }
}

/*
    A function which prints the tree in form of in-order.
    @param *root: The address of the root of the tree.
*/
void printInOrder(Node *root)
{
    if (root)
    {
        printInOrder(root -> left);
        printf("%d ", root -> value);
        printInOrder(root -> right);
    }
}

/*
    A function which prints the tree in form of post-order.
    @param *root: The address of the root of the tree.
*/
void printPostOrder(Node *root)
{
    if (root)
    {
        printPostOrder(root -> left);
        printPostOrder(root -> right);
        printf("%d ", root -> value);
    }
}