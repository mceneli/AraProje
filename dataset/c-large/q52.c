// https://www.hackerrank.com/challenges/flatland-space-stations

#include <stdio.h>
#include <stdlib.h>

void mergeSort(int A[], int l, int r);
int main()
{
    int n, m, max = 0;
    scanf("%d %d", &n, &m);
    int *A = malloc(n*sizeof(int));

    for (int i = 0; i < m; i++)
        scanf("%d", &A[i]);

    mergeSort(A, 0, m-1);

    for (int i = 0; i < m-1; i++)
        if (A[i+1] - A[i] > max)
            max = A[i+1] - A[i];

    if (n-1-A[m-1] > max && n-1-A[m-1] > A[0])
        printf("%d\n", n-1-A[m-1]);
    else if (A[0] > max)
        printf("%d\n", A[0]);
    else
        printf("%d\n", max/2);

    free(A);
    return 0;
}

void merge(int A[], int l, int m, int r);
void mergeSort(int A[], int l, int r)
{
    if (l < r)
    {
        int m = (l+r)/2;
        mergeSort(A, l, m);
        mergeSort(A, m+1, r);
        merge(A, l, m, r);
    }
}

void merge(int A[], int l, int m, int r)
{
    int n1 = m-l+1, n2 = r-m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = A[l+i];

    for (int j = 0; j < n2; j++)
        R[j] = A[m+1+j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        A[k] = L[i];
        i++, k++;
    }

    while (j < n2)
    {
        A[k] = R[j];
        j++, k++;
    }
}