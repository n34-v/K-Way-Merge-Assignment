# K-Way Merge Trace (Min Heap)

Heap is stored as an array. Notation: `value(source list)`.
Comparison rule: one comparison = one comparison between two heap-node values.
Extract: the minimum is removed, the last node moves to the root, then goes down.
Insert: the new node goes at the end, then goes up.

## Step 0: Build the initial heap

| Operation | Inserted | Comparisons | Heap State |
|-----------|----------|-------------|------------|
| Insert | 10 (L1) | 0 (heap empty) | [10(L1)] |
| Insert | 20 (L2) | 1 (20 vs parent 10) | [10(L1), 20(L2)] |
| Insert | 15 (L3) | 1 (15 vs parent 10) | [10(L1), 20(L2), 15(L3)] |

Initial heap contains 10, 20, 15. Comparisons so far: 2.

## Main trace

| Step | Deleted Min | Source List | Heap After Deletion | Inserted | Heap After Insertion | Comparisons (delete + insert) | Output |
|------|-------------|-------------|---------------------|----------|----------------------|-------------------------------|--------|
| 1 | 10 | L1 | [15(L3), 20(L2)] | 30 (L1) | [15(L3), 20(L2), 30(L1)] | 1 + 1 | 10 |
| 2 | 15 | L3 | [20(L2), 30(L1)] | 35 (L3) | [20(L2), 30(L1), 35(L3)] | 1 + 1 | 10 15 |
| 3 | 20 | L2 | [30(L1), 35(L3)] | 40 (L2) | [30(L1), 35(L3), 40(L2)] | 1 + 1 | 10 15 20 |
| 4 | 30 | L1 | [35(L3), 40(L2)] | 50 (L1) | [35(L3), 40(L2), 50(L1)] | 1 + 1 | 10 15 20 30 |
| 5 | 35 | L3 | [40(L2), 50(L1)] | 55 (L3) | [40(L2), 50(L1), 55(L3)] | 1 + 1 | 10 15 20 30 35 |
| 6 | 40 | L2 | [50(L1), 55(L3)] | 60 (L2) | [50(L1), 55(L3), 60(L2)] | 1 + 1 | 10 15 20 30 35 40 |
| 7 | 50 | L1 | [55(L3), 60(L2)] | 70 (L1) | [55(L3), 60(L2), 70(L1)] | 1 + 1 | 10 15 20 30 35 40 50 |
| 8 | 55 | L3 | [60(L2), 70(L1)] | 75 (L3) | [60(L2), 70(L1), 75(L3)] | 1 + 1 | 10 15 20 30 35 40 50 55 |
| 9 | 60 | L2 | [70(L1), 75(L3)] | 80 (L2) | [70(L1), 75(L3), 80(L2)] | 1 + 1 | 10 15 20 30 35 40 50 55 60 |
| 10 | 70 | L1 | [75(L3), 80(L2)] | none (L1 finished) | [75(L3), 80(L2)] | 1 + 0 | 10 15 20 30 35 40 50 55 60 70 |
| 11 | 75 | L3 | [80(L2)] | none (L3 finished) | [80(L2)] | 0 + 0 | 10 15 20 30 35 40 50 55 60 70 75 |
| 12 | 80 | L2 | [] | none (L2 finished) | [] | 0 + 0 | 10 15 20 30 35 40 50 55 60 70 75 80 |

## Totals (match the program output)

| Counter | Value |
|---------|-------|
| Comparisons | 2 (build) + 9 x 2 (steps 1-9) + 1 (step 10) = **21** |
| Heap insertions | 3 + 9 = **12** |
| Heap extractions | **12** |
| Maximum heap size | **3** |

## Note on Step 2

After deleting 15, the last node 30(L1) moves to the root: [30(L1), 20(L2)].
The program compares the left child 20 with 30. Since 20 < 30 they swap, giving [20(L2), 30(L1)].
That is the one comparison counted for this deletion.
