# Comparison: K-Way Min Heap vs Pairwise Merge

Input: L1, L2, L3 (4 elements each), N = 12, k = 3.
Numbers marked "measured" come from running the C programs (see `output/`).

Counting rules:
- Heap: comparison = comparison between two heap-node values.
- Pairwise: comparison = comparison between one element of each list being merged.
- Major operations (heap) = comparisons + insertions + extractions.
- Major operations (pairwise) = comparisons + element copies.

| Parameter | K-way Min Heap | Pairwise Merge |
|-----------|----------------|----------------|
| Data structure | Arrays + Min Heap of (value, list number) nodes | Arrays only |
| Heap size | Maximum 3 (= k), measured | Not applicable (no heap) |
| Number of comparisons | 21 (measured) | 18 (measured: 7 + 11) |
| Heap insertions / extractions | 12 / 12 (measured) | Not applicable |
| Element copies | Not counted separately (12 output elements) | 20 (measured: 8 + 12) |
| Major operations | 45 (21 + 12 + 12) | 38 (18 + 20) |
| Time complexity | O(N log k) | O(N k) sequential; O(N log k) if balanced |
| Space complexity | O(k) heap + O(N) output | O(N) intermediate arrays + O(N) output |
| Intermediate storage | None except the heap | Intermediate list of 8 elements (L1 + L2) |
| Implementation complexity | Higher (insert and extract-min with heapify) | Lower (one simple merge function) |
| Scalability as k grows | Good: each element costs about log k | Sequential version slows down: earlier elements are re-copied in every merge |
| Handling many sorted files | Only k elements in memory at a time | Needs many intermediate lists, or a tournament plan |

## Observation

For this small input (k = 3), pairwise merge used fewer comparisons (18 vs 21) and fewer major operations (38 vs 45). The heap has overhead that pays off only for larger k. The heap's advantage comes from the complexity analysis (O(N log k) vs O(N k)) and its small O(k) memory, not from these particular measurements.
