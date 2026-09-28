# Pairwise Merge Trace

Comparison rule: one comparison = comparing one element of list A with one element of list B.
Copying the leftover tail of a list needs no comparison.

## Step 1: L1 + L2

L1 = 10 30 50 70, L2 = 20 40 60 80

| # | Elements Compared | Element Taken | Result So Far |
|---|-------------------|---------------|---------------|
| 1 | 10 vs 20 | 10 | 10 |
| 2 | 30 vs 20 | 20 | 10 20 |
| 3 | 30 vs 40 | 30 | 10 20 30 |
| 4 | 50 vs 40 | 40 | 10 20 30 40 |
| 5 | 50 vs 60 | 50 | 10 20 30 40 50 |
| 6 | 70 vs 60 | 60 | 10 20 30 40 50 60 |
| 7 | 70 vs 80 | 70 | 10 20 30 40 50 60 70 |

L1 is finished, so 80 is copied from L2 without a comparison.

- Comparisons in Step 1: **7**
- Intermediate merged list: **10 20 30 40 50 60 70 80**

## Step 2: (L1 + L2) + L3

A = 10 20 30 40 50 60 70 80, L3 = 15 35 55 75

| # | Elements Compared | Element Taken | Result So Far |
|---|-------------------|---------------|---------------|
| 1 | 10 vs 15 | 10 | 10 |
| 2 | 20 vs 15 | 15 | 10 15 |
| 3 | 20 vs 35 | 20 | 10 15 20 |
| 4 | 30 vs 35 | 30 | 10 15 20 30 |
| 5 | 40 vs 35 | 35 | 10 15 20 30 35 |
| 6 | 40 vs 55 | 40 | 10 15 20 30 35 40 |
| 7 | 50 vs 55 | 50 | 10 15 20 30 35 40 50 |
| 8 | 60 vs 55 | 55 | 10 15 20 30 35 40 50 55 |
| 9 | 60 vs 75 | 60 | 10 15 20 30 35 40 50 55 60 |
| 10 | 70 vs 75 | 70 | 10 15 20 30 35 40 50 55 60 70 |
| 11 | 80 vs 75 | 75 | 10 15 20 30 35 40 50 55 60 70 75 |

L3 is finished, so 80 is copied from A without a comparison.

- Comparisons in Step 2: **11**
- Final merged list: **10 15 20 30 35 40 50 55 60 70 75 80**

## Summary

| Stage | Comparisons | Element Copies |
|-------|-------------|----------------|
| L1 + L2 | 7 | 8 |
| Result + L3 | 11 | 12 |
| **Total** | **18** | **20** |
