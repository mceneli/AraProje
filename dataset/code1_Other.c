#include <stdio.h>
#include <stdlib.h>

int main()
{
    srand(time(NULL)); // to making rand() function works correctly 

    int N; // number of cash points
    int X; // capacity of cash points
    int *pX = &X; // pointer of X
    int C; // number of coming customers
    int L; // number of leaving customers
    int customers = 0; // number of current customers
    int openCashPoints = 1; // number of open cash points

    printBanner(); // printing logo/banner of the program
    printf(COLOR_YELLOW "\tGood morning cashier! Have a good day.\n\n\n" COLOR_RESET);
    printf("  How many cash points are there in the hypermarket?: ");
    scanf("%d", &N);
    printf("  What is the capacity of a cash point?: ");
    scanf("%d", &X);

    // creating a dynamically allocated array that stores the cash informations
    int *CashPoints = (int *)malloc(openCashPoints*sizeof(int));

    // checking whether does the memory allows to create the dynamically array or not,
    // if not, then the program ends
    if (!CashPoints)
    {
        system("clear");
        printf("Not enough space!\n");
        exit(0);
    }

    int firstX = X; // number of X in the beginning
    char choice = 'Y'; // a char variable for users choice; Y represents YES, N represents NO

    // a loop that continues until the user press to the Y
    while (toupper(choice) != 'N')
    {
        system("clear"); // cleaning the screen
        printBanner();

        // number of coming and leaving customers determines randomly
        C = 1 + rand() % 10;
        L = 1 + rand() % 5;

        // difference between C and L adds to the customers variable
        customers += C-L;

        // number of customers can not be less than 0
        if (customers < 0)
            customers = 0;

        printf("\t%s%d%s customers came and ", COLOR_GREEN, C, COLOR_RESET);
        printf("%s%d%s customers left\n", COLOR_RED, L, COLOR_RESET);
        printf(COLOR_RESET "\tCurrent customers: %d\n\n\n", customers);

        // calling the function to change the capacity of check points if it needs
        changeCapacity(pX, firstX, customers, N);

        // calling the function to managing the number of cash points and the number of 
        // customers on the cash points.
        openCashPoints = cashOperations(CashPoints, openCashPoints, customers, N, X);

        printf(COLOR_YELLOW "\tCash Points:\n");
        printf("\t------------\n\n" COLOR_RESET);

        for (int i = 0; i < openCashPoints; i++)
            printf(COLOR_MAGENTA "\tCash #%d: %s%d customers\n", i+1, COLOR_BLUE, CashPoints[i]);

        printf(COLOR_RESET "\n\n\tPress Y to update or press N to exit: ");
        scanf(" %c", &choice); // getting choice from user
    }

    system("clear");
    printBanner();
    printf(COLOR_YELLOW "\tGood evening cashier! See you tomorrow.\n\n\n" COLOR_RESET);

    // cleaning the dynamically array from the heap 
    // it may not necessary, this line is end of the program already
    free(CashPoints);

    return 0;
}