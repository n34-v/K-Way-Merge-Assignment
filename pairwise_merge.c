/*
 * pairwise_merge.c
 * Simple pairwise merge:
 * First merge L1 and L2,
 * then merge the result with L3.
 */

#include <stdio.h>

#define N 4

int comparisons = 0;
int copies = 0;

/* Merge two sorted lists */
int merge(int a[], int n, int b[], int m, int result[])
{
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < n && j < m)
    {
        comparisons++;

        if (a[i] <= b[j])
        {
            printf("Compare %d and %d -> take %d\n",
                   a[i], b[j], a[i]);

            result[k] = a[i];
            i++;
        }
        else
        {
            printf("Compare %d and %d -> take %d\n",
                   a[i], b[j], b[j]);

            result[k] = b[j];
            j++;
        }

        k++;
        copies++;
    }

    /* Copy remaining elements of first list */
    while (i < n)
    {
        result[k] = a[i];
        i++;
        k++;
        copies++;
    }

    /* Copy remaining elements of second list */
    while (j < m)
    {
        result[k] = b[j];
        j++;
        k++;
        copies++;
    }

    return k;
}

/* Display a list */
void print_list(int arr[], int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int main()
{
    /*
     * Given lists
     *
     * L1 = 10 30 50 70
     * L2 = 20 40 60 80
     * L3 = 15 35 55 75
     */

    int L1[N] = {10, 30, 50, 70};
    int L2[N] = {20, 40, 60, 80};
    int L3[N] = {15, 35, 55, 75};

    int temp[2 * N];
    int final[3 * N];

    int temp_size;
    int final_size;

    int comparisons_step1;
    int comparisons_step2;

    int copies_step1;
    int copies_step2;

    printf("=============================================\n");
    printf("              PAIRWISE MERGE\n");
    printf("=============================================\n\n");

    printf("Input Lists:\n");

    printf("L1: ");
    print_list(L1, N);

    printf("L2: ");
    print_list(L2, N);

    printf("L3: ");
    print_list(L3, N);

    /*
     * STEP 1:
     * Merge L1 and L2
     */

    printf("\n---------------------------------------------\n");
    printf("         STEP 1: L1 + L2\n");
    printf("---------------------------------------------\n");

    temp_size = merge(L1, N, L2, N, temp);

    comparisons_step1 = comparisons;
    copies_step1 = copies;

    printf("\nIntermediate Result: ");
    print_list(temp, temp_size);

    printf("Comparisons in Step 1: %d\n",
           comparisons_step1);

    printf("Copies in Step 1: %d\n",
           copies_step1);

    /*
     * STEP 2:
     * Merge intermediate result with L3
     */

    printf("\n---------------------------------------------\n");
    printf("         STEP 2: (L1 + L2) + L3\n");
    printf("---------------------------------------------\n");

    final_size = merge(temp, temp_size, L3, N, final);

    comparisons_step2 = comparisons - comparisons_step1;
    copies_step2 = copies - copies_step1;

    printf("\nComparisons in Step 2: %d\n",
           comparisons_step2);

    printf("Copies in Step 2: %d\n",
           copies_step2);

    /*
     * FINAL RESULT
     */

    printf("\n---------------------------------------------\n");
    printf("              FINAL RESULT\n");
    printf("---------------------------------------------\n");

    printf("Merged List: ");
    print_list(final, final_size);

    /*
     * OPERATION COUNTS
     */

    printf("\n---------------------------------------------\n");
    printf("             OPERATION COUNTS\n");
    printf("---------------------------------------------\n");

    printf("Comparisons (Step 1) : %d\n",
           comparisons_step1);

    printf("Comparisons (Step 2) : %d\n",
           comparisons_step2);

    printf("Total Comparisons    : %d\n",
           comparisons);

    printf("Copies (Step 1)      : %d\n",
           copies_step1);

    printf("Copies (Step 2)      : %d\n",
           copies_step2);

    printf("Total Copies         : %d\n",
           copies);

    printf("Major Operations     : %d\n",
           comparisons + copies);

    printf("Largest Temporary Result : %d elements\n",
           temp_size);

    printf("\n=============================================\n");

    return 0;
}