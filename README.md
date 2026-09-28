# K-Way Merge Using Min Heap vs Pairwise Merge

## 1. Introduction

Merging sorted lists is a basic step in many systems, e.g. combining sorted transaction logs or the merge phase of external sorting. This project implements two ways of merging several sorted lists in C and compares them using measured operation counts and complexity analysis.

## 2. Problem Statement

A financial system receives three already sorted transaction lists:

- L1 = 10, 30, 50, 70
- L2 = 20, 40, 60, 80
- L3 = 15, 35, 55, 75

Merge them into one sorted list using (a) a k-way merge with a Min Heap and (b) a simple pairwise merge, then compare both approaches.

## 3. Objectives

- Implement a k-way merge using a Min Heap in C.
- Implement a pairwise merge in C.
- Show important heap states and record trace tables.
- Count operations inside the programs (no invented numbers).
- Analyse time and space complexity and decide which approach suits many sorted files.

## 4. Input Data

File: [`input/input.txt`](input/input.txt)

```
L1: 10 30 50 70
L2: 20 40 60 80
L3: 15 35 55 75
```

## 5. Data Structures

- **Arrays:** each list is an array; `next_index[i]` remembers the next unused element of list i. The output is also an array.
- **Min Heap:** an array-based complete binary tree where every parent is <= its children. Parent of index i is (i-1)/2; children are 2i+1 and 2i+2. The smallest value is always at index 0.
- **Heap node:** a `struct` holding `value` and `list_no`. `list_no` tells us which list to take the next element from after deleting the minimum.

```c
typedef struct {
    int value;
    int list_no;   /* 0 = L1, 1 = L2, 2 = L3 */
} HeapNode;
```

## 6. K-way Min Heap Algorithm

1. Insert the first element of every list into the Min Heap (value + source list).
2. Remove the minimum from the heap and append it to the output.
3. Insert the next element from the same list (if any).
4. Repeat steps 2-3 until the heap is empty.

Counting rule: 1 comparison = comparing two heap-node values (during insert and extract).

## 7. Pairwise Merge Algorithm

1. Merge L1 and L2 into a temporary sorted list.
2. Merge that temporary list with L3 to get the final list.
3. Each merge compares the front elements of the two lists and copies the smaller one.

Counting rule: 1 comparison = comparing one element from each list. Copying a leftover tail needs no comparison.

## 8. Execution Results

**K-way** ([`output/k_way_output.txt`](output/k_way_output.txt)):

| Event | Heap State |
|-------|------------|
| Initial heap after 3 inserts | [10(L1), 20(L2), 15(L3)] |
| Extract 10 | [15(L3), 20(L2)] |
| Insert 30 (from L1) | [15(L3), 20(L2), 30(L1)] |
| Extract 15 | [20(L2), 30(L1)] |
| Insert 35 (from L3) | [20(L2), 30(L1), 35(L3)] |
| Extract 70 (L1 finished) | [75(L3), 80(L2)] |
| Extract 75 (L3 finished) | [80(L2)] |
| Extract 80 (L2 finished) | [] |

```
      10(L1)                  15(L3)
     /      \                /      \
 20(L2)    15(L3)        20(L2)    30(L1)
   initial heap        after extract 10, insert 30
```

**Pairwise** ([`output/pairwise_output.txt`](output/pairwise_output.txt)):

| Stage | Result | Comparisons |
|-------|--------|-------------|
| L1 + L2 | 10 20 30 40 50 60 70 80 | 7 |
| (L1+L2) + L3 | 10 15 20 30 35 40 50 55 60 70 75 80 | 11 |

Final merged output of both programs:

```
10 15 20 30 35 40 50 55 60 70 75 80
```

## 9. K-way Trace

[traces/k_way_trace.md](traces/k_way_trace.md)

## 10. Pairwise Trace

[traces/pairwise_trace.md](traces/pairwise_trace.md)

## 11. Operation Count

All values are printed by the programs.

| Measure | K-way Min Heap | Pairwise Merge |
|---------|----------------|----------------|
| Comparisons | 21 | 18 (7 + 11) |
| Heap insertions | 12 | - |
| Heap extractions | 12 | - |
| Element copies | - | 20 (8 + 12) |
| Maximum heap size | 3 | - |
| Major operations | 45 (comparisons + insertions + extractions) | 38 (comparisons + copies) |

## 12. Complexity Analysis

N = total elements, k = number of lists.

| | K-way Min Heap | Sequential Pairwise (used here) | Balanced Pairwise |
|--|----------------|-------------------------------|-------------------|
| Time | O(N log k) | O(N k) | O(N log k) |
| Extra space | O(k) heap | O(N) intermediate arrays | O(N) |
| Output space | O(N) | O(N) | O(N) |

- The heap holds at most k nodes, so each insert/extract costs O(log k), and there are N of each.
- Merging two lists of sizes n and m costs O(n + m). In sequential merging the growing result is copied again in every merge, giving about N k / 2 work.
- Pairwise merging is not always O(N^2). Balanced pairwise merging can also reach O(N log k).

Details: [analysis/complexity.md](analysis/complexity.md)

## 13. Comparison Table

| Parameter | K-way Min Heap | Pairwise Merge |
|-----------|----------------|----------------|
| Data structure | Arrays + Min Heap | Arrays |
| Heap size | 3 (= k) | Not applicable |
| Comparisons | 21 | 18 |
| Major operations | 45 | 38 |
| Time complexity | O(N log k) | O(N k) sequential |
| Space | O(k) heap + O(N) output | O(N) intermediate + O(N) output |
| Implementation | More complex | Simpler |
| Many sorted files | Scales well | Needs many intermediate lists |

Full table: [analysis/comparison.md](analysis/comparison.md)

## 14. Visualizations

![Project Flow](images/project_flow.png)

![K-way Heap](images/k_way_heap.png)

![Performance Comparison](images/performance_comparison.png)

## 15. Final Conclusion

- **Measured operations (k = 3):** pairwise used fewer comparisons (18 vs 21) and fewer major operations (38 vs 45). For this small input the simple pairwise method is slightly cheaper.
- **Heap size:** never exceeded k = 3 nodes.
- **Complexity:** the heap gives O(N log k); sequential pairwise is O(N k).
- **Space:** the heap needs only O(k) extra space; pairwise needs intermediate arrays up to O(N).
- **Scalability:** as the number of sorted files grows, log k grows far more slowly than k, so the **k-way Min Heap is the more suitable approach for many sorted files**, especially for large or file-based data, since only k elements are needed in memory at a time.

The conclusion about larger k rests on the complexity analysis. The measurements here are only for k = 3.

## 16. How to Compile and Run

Run from the project root folder (programs read `input/input.txt`).

Linux / macOS / Git Bash:
```
gcc src/k_way_merge.c -o kway
./kway

gcc src/pairwise_merge.c -o pairwise
./pairwise
```

Windows (MinGW):
```
gcc src\k_way_merge.c -o kway.exe
kway.exe

gcc src\pairwise_merge.c -o pairwise.exe
pairwise.exe
```

## 17. Repository Structure

```
K-Way-Merge-Assignment/
├── README.md
├── src/
│   ├── k_way_merge.c
│   └── pairwise_merge.c
├── input/
│   └── input.txt
├── output/
│   ├── k_way_output.txt
│   └── pairwise_output.txt
├── traces/
│   ├── k_way_trace.md
│   └── pairwise_trace.md
├── analysis/
│   ├── complexity.md
│   └── comparison.md
└── images/
    ├── project_flow.png
    ├── k_way_heap.png
    └── performance_comparison.png
```

## Uploading to GitHub

```
git init
git add .
git commit -m "Initial commit: K-way merge assignment"
git branch -M main
git remote add origin <repository-url>
git push -u origin main
```
