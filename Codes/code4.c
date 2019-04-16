/*
    Data Structures and Algorithms - Assignment 2 - Q2

    @author
    Student: Osman Araz
    Student NO: 16011020
    Delivery Date: 02.04.2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    A structure for binary search tree. Each node consist the name, surname, id number, number of friends,
    array of his/hers friends and the capacity of the array of a user. And also addresses of left and right
    nodes of the node.
*/
typedef struct BST
{
    char name[20], surname[30];
    int id, num_of_friends, friend_capacity, *friends;
    struct BST *left, *right;
} Node;

Node *getUsersFromFile(FILE *, Node *);
Node *deleteUser(Node *, int);
void contains(Node *, int);
void Friends(Node *, int);
int size(Node *);
void printNext(Node *, int);
void printGreater(Node *, int);
void printInOrder(Node *);
int main()
{
    
    Node *root = NULL;  // address of the root of the tree initializing as NULL
    FILE *fi = fopen("input2.txt", "r");    // opening the file in reading mode
    root = getUsersFromFile(fi, root);      // getting users to the tree from the file
                                            // the function returns the address of the root of the tree
    fclose(fi);     // closing the file

    // printing the tree in form of in-order
    printf("In-Ordered Tree:\n");
    printInOrder(root);
    printf("\nSize of the tree: %d\n\n", size(root));

    int searchID;   // a variable to get ID which will be searched on the tree from the user

    // The below lines of code are for testing the created functions.
    
    for (int i = 0; i < 2; ++i)
    {
        printf("ID of the user which will be deleted: ");
        scanf("%d", &searchID);
        root = deleteUser(root, searchID);
        printf("\nIn-Ordered Tree after the deletion:\n");
        printInOrder(root);
        printf("\nSize of the tree: %d\n", size(root));
    }

    for (int i = 0; i < 2; ++i)
    {
        printf("\nID of the user which will be searched: ");
        scanf("%d", &searchID);
        contains(root, searchID);
    }

    printf("\n");

    for (int i = 0; i < 2; ++i)
    {
        printf("\nID of the user which will be printed his/hers friends: ");
        scanf("%d", &searchID);
        Friends(root, searchID);
    }

    printf("\n");

    for (int i = 0; i < 2; ++i)
    {
        printf("\nID of the user which will be printed his/hers subtree: ");
        scanf("%d", &searchID);
        printNext(root, searchID);
    }

    printf("\n");

    for (int i = 0; i < 2; ++i)
    {
        printf("\nID of the user which will be printed users who have greater ID number from the user: ");
        scanf("%d", &searchID);
        printGreater(root, searchID);
    }

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
    A function which getting users to the tree from a file.
    @param *fi: The pointer of the file.
    @param *root: The address of the root of the tree.
    @return: The updated address of the root of the tree.
*/
Node *createNode();
void addFriend(Node *, int);
Node *insertNewUser(Node *, Node *);
Node *getUsersFromFile(FILE *fi, Node *root)
{
    char line[200]; // a temporary string to get line from the file
    
    while (fgets(line, 200, fi)) // getting lines from the file
    {
        Node *newUser = createNode();   // creating a new node

        // assigning the elements of the node with strtok() function:
        newUser -> id = atoi(strtok(line, ", "));
        strcpy(newUser -> name, strtok(NULL, ", "));
        strcpy(newUser -> surname, strtok(NULL, ", "));
        char *numbers = strtok(NULL, ",");

        // adding the friends to the array of the friends of a user
        if (numbers)
            newUser -> friends[newUser -> num_of_friends++] = atoi(strtok(numbers, "-"));
        
        while (numbers = strtok(NULL, "-"))
            addFriend(newUser, atoi(numbers));

        root = insertNewUser(root, newUser);   // inserting the user to the tree 
    }

    return root;  // returning the root of the tree
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

    // initializing the values of the node:
    newNode -> num_of_friends = 0;
    newNode -> friend_capacity = 10;
    newNode -> friends = (int *)malloc(newNode -> friend_capacity*sizeof(int));
    newNode -> left = NULL;
    newNode -> right = NULL;

    return newNode; // returning the address of the created node
}

/*
    A function which adds a friend to a user's friend list.
    @param *user: The addres of the user.
    @param newFriend: The ID of the friend.
*/
void addFriend(Node *user, int newFriend)
{
    // if the number of friends reaches the capacity, then the capacity extends:
    if (user -> num_of_friends == user -> friend_capacity)
    {
        user -> friend_capacity *= 2;
        user -> friends = realloc(user -> friends, user -> friend_capacity);
    }

    user -> friends[user -> num_of_friends++] = newFriend;  // the friend adding to the list
}

/*
    A function which insert a node to the binary search tree.
    @param *root: The address of the root of the tree.
    @param *newUser: The addresss of the node which will be added to the tree.
    @return: The address of the root of the updated tree.
*/
Node *insertNewUser(Node *root, Node *newUser)
{
    if (!root)  // if the root is NULL, then the new node will be the root
        return newUser;

    Node *iter = root;  // an iterator which will be moved on on the list

    while (iter)
    {
        // if ID of the new node is less than the ID of the iterator, then the iterator goes to
        // the left child, if the left child is NULL, then the left child will be the new node
        if (newUser -> id < iter -> id)
        {
            if (iter -> left)
                iter = iter -> left;
            else
            {
                iter -> left = newUser;
                iter = NULL;
            }
        }
        // if ID of the new node is greater or equal than the ID of the iterator, then the iterator goes
        // to the right child, if the right child is NULL, then the right child will be the new node
        else
        {
            if (iter -> right)
                iter = iter -> right;
            else
            {
                iter -> right = newUser;
                iter = NULL;
            }
        }
    }
    
    return root;  // returning the addres of the root of the tree
}

/*
    A function which deletes a node from a tree.
    @param *root: The address of the root of the tree.
    @param deleteID: The ID of the user which will be deleted.
    @return: The updated address of the root of the tree.
*/
void copyUser(Node *, Node *);
void deallocateUser(Node *);
Node *minNodeAtRightSubtree(Node *);
Node *deleteUser(Node *root, int deleteID)
{
    if (!root)  // if the current node is null, then the function returns NULL
        return NULL;
    else if (deleteID < root -> id) // if the value of the current node is less than the given ID
        root -> left = deleteUser(root -> left, deleteID);
    else if (deleteID > root -> id) // if the value of the current node is greater than the given ID
        root -> right = deleteUser(root -> right, deleteID);
    else                            // if the value of the current node is equal to the given ID
    {
        if (!root -> left && !root -> right) // if the node has no child
        {
            deallocateUser(root);   // deallocting the node and its array of friends
            root = NULL;
        }
        else if (!root -> left)     // if the node has only right child
        {
            Node *temp = root;
            root = root -> right;   
            deallocateUser(temp);   // deallocting the node and its array of friends
        }
        else if (!root -> right)    // if the node has only left child
        {
            Node *temp = root;
            root = root -> left;
            deallocateUser(temp);   // deallocting the node and its array of friends
        }
        else    // if node has left and right children
        {
            // gettiing the node which has the minimum ID number on the right subtree of the node
            Node *temp = minNodeAtRightSubtree(root -> right);
            copyUser(root, temp);   // copying the found node to the current node
            root -> right = deleteUser(root -> right, temp -> id);  // deleting the duplicate from the tree
        }
    }

    return root;  // returning the addres of the root of the tree
}

/*
    A function which finds the minimum value of a subtree.
    @param *root: The address of the root of the subtree.
    @return: The address of the found node.
*/
Node *minNodeAtRightSubtree(Node *root)
{
    while (root -> left)
        root = root -> left;

    return root;
}

/*
    A function which dealloctes a node and its array of friends.
    @param *user: The address of the node.
*/
void deallocateUser(Node *user)
{
    free(user -> friends);
    free(user);
}

/*
    A function which copy elements of the source node the target node.
    @param *target: The address of the target node.
    @param *source: The address of the source node.
*/
void copyUser(Node *target, Node *source)
{
    target -> id = source -> id;
    strcpy(target -> name, source -> name);
    strcpy(target -> surname, source -> surname);
    target -> num_of_friends = source -> num_of_friends;
    target -> friend_capacity = source -> friend_capacity;
    memcpy(target -> friends, source -> friends, source -> num_of_friends*sizeof(int));
}

/*
    A function which search a user on a tree.
    @param *root: The address of the root of the tree.
    @param userID: The ID of the user which will be searched on the tree.
    @return: If the user found on the tree, it returns the found node. 
    Otherwise it returns NULL.
*/
Node *searchUser(Node *root, int userID)
{
    if (!root)
        return NULL;
    else if (userID == root -> id)
        return root;
    else if (userID < root -> id)
        return searchUser(root -> left, userID);
    
    return searchUser(root -> right, userID);
}

/*
    A function which gets user ID and prints the name and surname of the user.
    @param *root: The address of the root of the tree.
    @param userID: The ID of the user which will be searched on the tree.
*/
void contains(Node *root, int userID)
{
    Node *user = searchUser(root, userID);
    
    if (user)
        printf("%s %s\n", user -> name, user -> surname);
    else
        printf("user could not be found or a deleted user\n");
}

/*
    A function which prints friends of a user.
    @param *root: The address of the root of the tree.
    @param userID: The ID of the user which will be searched on the tree.
*/
void Friends(Node *root, int userID)
{
    Node *user = searchUser(root, userID);
    
    if (user)
    {
        printf("Friends of %s %s: \n", user -> name, user -> surname);
        
        for (int i = 0; i < user -> num_of_friends; ++i)
        {
            printf(" - ");
            contains(root, user -> friends[i]);
        }
    }
    else
        printf("user could not be found or a deleted user\n");
}

/*
    A function which finds the size of the tree.
    @param *root: The address of the root of the tree.
    @return: The size of the tree.
*/
int size(Node *root)
{
    if (!root)
        return 0;
    
    return 1 + size(root -> left) + size(root -> right);
}

/*
    A function which prints the subtree which rooted as a given node.
    @param *root: The address of the root of the tree.
    @param userID: The ID of the user which will be searched on the tree.
*/
void printNext(Node *root, int userID)
{
    Node *user = searchUser(root, userID);
    
    if (user)
    {
        printf("Subtree for %s %s:\n", user -> name, user -> surname);
        printInOrder(user);
    }
    else
        printf("user could not be found or a deleted user\n");
}

/*
    A function which prints the users which have greater ID numbers from a given user.
    The function basically prints the right subtree of the node and prints all right 
    subtrees of its ancestors.
    @param *root: The address of the root of the tree.
    @param userID: The ID of the user which will be searched on the tree.
*/
void printGreater(Node *root, int userID)
{
    if (root)
    {
        if (userID < root -> id)
        {
            printGreater(root -> left, userID);
            printf(" #%d - %s %s\n", root -> id, root -> name, root -> surname);
            printInOrder(root -> right);
        }
        else if (userID > root -> id)
            printGreater(root -> right, userID);
        else
            printInOrder(root -> right);
    }
}

/*
    A function which prints the tree in form of in-order.
    @param *root: The address of the root of the tree.
*/
void printInOrder(Node *temp)
{
    if (temp)
    {
        printInOrder(temp -> left);
        printf(" #%d - %s %s\n", temp -> id, temp -> name, temp -> surname);
        printInOrder(temp -> right);
    }
}