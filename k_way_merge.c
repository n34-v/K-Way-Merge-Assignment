/*
 * k_way_merge.c
 * K-way merge of 3 sorted lists using a Min Heap.
 *
 * Operation counting:
 * - Comparison = comparison between two heap-node values
 * - Insertion = inserting one element into the heap
 * - Extraction = removing the minimum element from the heap
 */

#include <stdio.h>

#define K 3
#define N 4
#define MAX_HEAP 10

/* Heap node */
typedef struct
{
    int value;
    int list_no;
} HeapNode;

HeapNode heap[MAX_HEAP];
int heap_size = 0;

/* Operation counters */
int comparisons = 0;
int insertions = 0;
int extractions = 0;
int max_heap_size = 0;

/* Swap two heap nodes */
void swap(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

/* Display current heap */
void print_heap()
{
    int i;

    printf("Heap = [");

    for (i = 0; i < heap_size; i++)
    {
        printf("%d(L%d)", heap[i].value, heap[i].list_no + 1);

        if (i < heap_size - 1)
            printf(", ");
    }

    printf("]  Size = %d\n", heap_size);
}

/* Insert element into Min Heap */
void insert_heap(HeapNode node)
{
    int i;
    int parent;

    i = heap_size;

    heap[heap_size] = node;
    heap_size++;

    insertions++;

    if (heap_size > max_heap_size)
        max_heap_size = heap_size;

    /* Move element upward */
    while (i > 0)
    {
        parent = (i - 1) / 2;

        comparisons++;

        if (heap[i].value < heap[parent].value)
        {
            swap(&heap[i], &heap[parent]);
            i = parent;
        }
        else
        {
            break;
        }
    }
}

/* Remove minimum element from Min Heap */
HeapNode extract_min()
{
    HeapNode min;
    int i;
    int left;
    int right;
    int smallest;

    min = heap[0];

    heap[0] = heap[heap_size - 1];
    heap_size--;

    extractions++;

    i = 0;

    /* Move root downward */
    while (1)
    {
        left = 2 * i + 1;
        right = 2 * i + 2;
        smallest = i;

        if (left < heap_size)
        {
            comparisons++;

            if (heap[left].value < heap[smallest].value)
                smallest = left;
        }

        if (right < heap_size)
        {
            comparisons++;

            if (heap[right].value < heap[smallest].value)
                smallest = right;
        }

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);

        i = smallest;
    }

    return min;
}

int main()
{
    /*
     * Given input lists
     *
     * L1 = 10 30 50 70
     * L2 = 20 40 60 80
     * L3 = 15 35 55 75
     */

    int lists[K][N] =
    {
        {10, 30, 50, 70},
        {20, 40, 60, 80},
        {15, 35, 55, 75}
    };

    int next_index[K];

    int output[K * N];

    int out_count = 0;

    int i;
    int j;

    HeapNode node;
    HeapNode min;

    /* Display input */
    printf("=============================================\n");
    printf("       K-WAY MERGE USING MIN HEAP\n");
    printf("=============================================\n\n");

    printf("Input Lists:\n");

    for (i = 0; i < K; i++)
    {
        printf("L%d: ", i + 1);

        for (j = 0; j < N; j++)
        {
            printf("%d ", lists[i][j]);
        }

        printf("\n");
    }

    /*
     * STEP 1:
     * Insert first element of each list.
     */

    printf("\n---------------------------------------------\n");
    printf("        BUILDING INITIAL MIN HEAP\n");
    printf("---------------------------------------------\n");

    for (i = 0; i < K; i++)
    {
        node.value = lists[i][0];
        node.list_no = i;

        next_index[i] = 1;

        insert_heap(node);

        printf("Insert %d from L%d -> ",
               node.value,
               i + 1);

        print_heap();
    }

    /*
     * STEP 2:
     * Extract minimum and insert the next
     * element from the same list.
     */

    printf("\n---------------------------------------------\n");
    printf("              MERGING PROCESS\n");
    printf("---------------------------------------------\n");

    while (heap_size > 0)
    {
        /* Extract minimum */
        min = extract_min();

        output[out_count] = min.value;
        out_count++;

        printf("\nExtract Min %d from L%d -> ",
               min.value,
               min.list_no + 1);

        print_heap();

        /*
         * Insert next element from the
         * same list if available.
         */

        i = min.list_no;

        if (next_index[i] < N)
        {
            node.value = lists[i][next_index[i]];
            node.list_no = i;

            next_index[i]++;

            insert_heap(node);

            printf("Insert %d from L%d -> ",
                   node.value,
                   i + 1);

            print_heap();
        }
        else
        {
            printf("L%d is finished. Nothing inserted.\n",
                   i + 1);
        }
    }

    /*
     * STEP 3:
     * Display final merged list.
     */

    printf("\n---------------------------------------------\n");
    printf("              FINAL RESULT\n");
    printf("---------------------------------------------\n");

    printf("Merged List: ");

    for (i = 0; i < out_count; i++)
    {
        printf("%d ", output[i]);
    }

    printf("\n");

    /*
     * STEP 4:
     * Display operation counts.
     */

    printf("\n---------------------------------------------\n");
    printf("             OPERATION COUNTS\n");
    printf("---------------------------------------------\n");

    printf("Comparisons       : %d\n", comparisons);
    printf("Heap Insertions   : %d\n", insertions);
    printf("Heap Extractions  : %d\n", extractions);
    printf("Maximum Heap Size : %d\n", max_heap_size);

    printf("\nTotal Operations  : %d\n",
           comparisons + insertions + extractions);

    printf("\n=============================================\n");

    return 0;
}