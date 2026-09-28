# Complexity Analysis

Let N = total number of elements (here 12) and k = number of sorted lists (here 3).

## 1. K-way merge using Min Heap

### Time complexity: O(N log k)

- The heap never holds more than k elements (one per list), so its height is about log k.
- Insert goes up at most log k levels: O(log k).
- Extract-min goes down at most log k levels: O(log k).
- Each of the N elements is inserted once and extracted once: N x O(log k).
- Building the first heap costs k inserts = O(k log k), never more than O(N log k).

**Total: O(N log k)**

### Space complexity

| Type of space | Size | Explanation |
|---------------|------|-------------|
| Auxiliary (heap) space | O(k) | one node per list, so at most k nodes at a time (max heap size = 3 in our run) |
| Output space | O(N) | the final merged list must be stored (or written to a file) anyway |

The heap is the *extra* space the algorithm needs. The output space is needed by any merging method, so it is kept separate.

## 2. Pairwise merge

### Merging two sorted lists of sizes n and m: O(n + m)

Look at the front of both lists, take the smaller one, move on. Each element is taken once, so work is proportional to n + m. Worst-case comparisons: n + m - 1.

### Merging k lists one after the other (the method used here)

Assume k lists of size n each, so N = k x n.

| Merge | Elements processed |
|-------|--------------------|
| L1 + L2 | 2n |
| (L1L2) + L3 | 3n |
| (L1L2L3) + L4 | 4n |
| ... | ... |
| last merge | kn |

Total work = n(2 + 3 + ... + k), about n k^2 / 2 = N k / 2.

**Sequential pairwise merge: O(N x k)**

This is **not** always O(N^2). It only approaches O(N^2) when k is close to N (almost every list has one element). For a small k like 3 it is only slightly more work than the heap approach.

In our run: step 1 copied 8 elements (2n), step 2 copied 12 (3n), matching the table.

### Balanced pairwise merge: O(N log k)

If lists are merged like a tournament (L1+L2, L3+L4, then those results together, and so on), there are about log k rounds, each processing N elements. So balanced pairwise merging is also **O(N log k)**.

However, it needs extra intermediate lists in every round. The simple sequential method used here keeps creating and re-copying a growing intermediate list, so it becomes less convenient as the number of sorted files increases.

### Space complexity

Each merge creates a new result array. The largest intermediate array can be O(N) (8 elements in our run), plus the O(N) final output. There is no O(k) heap, but intermediate arrays are much larger than the heap.

## 3. Summary

| | K-way Min Heap | Sequential Pairwise | Balanced Pairwise |
|--|----------------|---------------------|-------------------|
| Time | O(N log k) | O(N k) | O(N log k) |
| Auxiliary space | O(k) | O(N) | O(N) |
| Output space | O(N) | O(N) | O(N) |
