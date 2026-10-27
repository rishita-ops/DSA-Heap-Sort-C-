# DSA — Heap Sort (C++)

An in-place, comparison-based sorting algorithm that turns the array into a **max-heap** and then repeatedly pulls the largest element to the end. This implementation is **iterative** (no recursion) and reads its input from the console.

---

## Problem Statement

Given an array of `n` integers, sort it in **ascending order** using Heap Sort.

**Example**

```
Input:  n = 5, arr = [4, 10, 3, 5, 1]
Output: 1 3 4 5 10
```

---

## Solution

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter element " << i + 1 << ": ";
        cin >> arr[i];
    }

    for(int i=n/2-1;i>=0;i--)
    {
        int root=i;
        while(root*2+1<n)
        {
            int child=root*2+1;
            if(child+1<n && arr[child]<arr[child+1])
                child++;
            if(arr[root]<arr[child])
            {
                swap(arr[root],arr[child]);
                root=child;
            }
            else
                break;
        }
    }

    for(int i=n-1;i>=0;i--)
    {
        swap(arr[0],arr[i]);
        int root=0;
        while(root*2+1<i)
        {
            int child=root*2+1;
            if(child+1<i && arr[child]<arr[child+1])
                child++;
            if(arr[root]<arr[child])
            {
                swap(arr[root],arr[child]);
                root=child;
            }
            else
                break;
        }
    }

    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }

    return 0;
}
```

---

## The Critical Idea

An array can be read as a **complete binary tree** without any extra memory. For the element at index `i`:

| Relation     | Index     |
|--------------|-----------|
| Left child   | `2i + 1`  |
| Right child  | `2i + 2`  |
| Parent       | `(i-1)/2` |

A **max-heap** guarantees every parent is greater than or equal to its children, so the largest element always sits at index `0`. Heap Sort works in two phases:

1. **Build the heap** — rearrange the array into a max-heap.
2. **Extract the maximum** — swap the root with the last unsorted element, shrink the heap by one, and restore the heap property. Repeat.

Each extraction places one element in its final position, so the sorted region grows from the right.

---

## How the Loop Works

### Phase 1 — Build the Max-Heap

```cpp
for(int i = n/2 - 1; i >= 0; i--)
```

- Indices `n/2` to `n-1` are leaves, so they are already valid heaps. The loop starts at the **last non-leaf node** `n/2 - 1` and moves up to the root.
- For each `i`, the inner `while` loop does a **sift-down**: pick the larger child, and if it is bigger than `root`, swap and continue downward. Otherwise `break`.

### Phase 2 — Sort

```cpp
for(int i = n-1; i >= 0; i--)
{
    swap(arr[0], arr[i]);   // move current max to its final position
    // sift-down arr[0] within the heap of size i
}
```

- After the swap, the heap occupies indices `0 .. i-1` (size `i`), which is why the sift-down condition uses `< i` instead of `< n`.
- The sift-down restores the max-heap property for the shrunken heap.

---

## Pseudocode

```
HEAP-SORT(arr, n):
    for i = n/2 - 1 down to 0:
        SIFT-DOWN(arr, i, n)

    for i = n-1 down to 1:
        swap(arr[0], arr[i])
        SIFT-DOWN(arr, 0, i)

SIFT-DOWN(arr, root, size):
    while 2*root + 1 < size:
        child = 2*root + 1
        if child + 1 < size and arr[child] < arr[child + 1]:
            child = child + 1
        if arr[root] < arr[child]:
            swap(arr[root], arr[child])
            root = child
        else:
            break
```

---

## Dry Run

Input: `arr = [4, 10, 3, 5, 1]`, `n = 5`

**Phase 1 — Build the heap** (start at `i = n/2 - 1 = 1`)

| Step | Action | Array |
|------|--------|-------|
| i = 1 | `10` vs larger child `5` — already in place | `[4, 10, 3, 5, 1]` |
| i = 0 | `4` < `10` → swap | `[10, 4, 3, 5, 1]` |
| continue | `4` (index 1) < `5` (index 3) → swap | `[10, 5, 3, 4, 1]` |

Max-heap: `[10, 5, 3, 4, 1]`

**Phase 2 — Extract the maximum**

| i | Swap `arr[0]` ↔ `arr[i]` | Sift-down (heap size = i) | Array |
|---|--------------------------|---------------------------|-------|
| 4 | `10` ↔ `1` | `1` sinks below `5`, then `4` | `[5, 4, 3, 1, 10]` |
| 3 | `5` ↔ `1` | `1` sinks below `4` | `[4, 1, 3, 5, 10]` |
| 2 | `4` ↔ `3` | `3` vs child `1` — stays | `[3, 1, 4, 5, 10]` |
| 1 | `3` ↔ `1` | heap of size 1 | `[1, 3, 4, 5, 10]` |
| 0 | `1` ↔ `1` | nothing to do | `[1, 3, 4, 5, 10]` |

**Output:** `1 3 4 5 10`

---

## Complexity Analysis

| Case    | Time          | Space  |
|---------|---------------|--------|
| Best    | O(n log n)    | O(1)   |
| Average | O(n log n)    | O(1)   |
| Worst   | O(n log n)    | O(1)   |

- **Build heap:** O(n) — most nodes are near the bottom and sink only a few levels.
- **n extractions:** each sift-down costs O(log n), giving O(n log n) overall.
- **Space:** sorting is done in place; only a handful of integer variables are used beyond the input array.
- **Stability:** Heap Sort is **not stable** — equal elements may change their relative order.

---

## Edge Cases

| Input | Behaviour |
|-------|-----------|
| `n = 1` | The build loop doesn't run and the single element is printed as is |
| Already sorted | Still O(n log n) — the heap is built and fully unwound |
| Reverse sorted | Same O(n log n) bound |
| All equal elements | Comparisons use strict `<`, so no needless swaps occur during sift-down |
| Negative numbers | Handled naturally, since only comparisons are used |
| Duplicates | Sorted correctly, but their original relative order is not preserved |

---

## Code-Quality Notes

- `int arr[n];` is a **variable-length array (VLA)**, which is a GCC/Clang extension and not standard C++. For portable code and large `n`, prefer `vector<int> arr(n);`.
- `#include<bits/stdc++.h>` is GCC-specific — ideal for competitive programming, but in production code include only the headers you need (`<iostream>`, `<algorithm>`).
- The sift-down logic is written twice (build phase and sort phase). Extracting it into a helper function would remove the duplication.
- The final loop runs down to `i = 0`, which performs a harmless self-swap; stopping at `i >= 1` is equivalent.

---

## Natural Extension

- Extract `siftDown(arr, root, size)` into a reusable function.
- Sort in **descending** order by using a min-heap (flip the comparisons).
- Replace the hand-written heap with `std::priority_queue` or `std::make_heap` / `std::sort_heap`.
- Use Heap Sort's heap-building step to solve **Top-K** problems.

---

## Repository Structure

```
DSA/
└── Sorting/
    └── Heap-Sort/
        ├── heap_sort.cpp
        └── README.md
```

---

## How to Run

```bash
g++ heap_sort.cpp -o heap_sort
./heap_sort
```

**Sample session**

```
Enter the number of elements: 5
Enter element 1: 4
Enter element 2: 10
Enter element 3: 3
Enter element 4: 5
Enter element 5: 1
1 3 4 5 10
```

---

## Key Concepts

- **Complete binary tree in an array** — parent and child positions come from index arithmetic
- **Max-heap property** — every parent ≥ its children
- **Sift-down (heapify)** — restores the heap after a change at the root
- **In-place sorting** — O(1) auxiliary space
- **Selection-style sorting** — repeatedly selects the maximum, but in O(log n) instead of O(n)

---

## Why This Problem Matters

Heap Sort is the classic example of getting a **guaranteed O(n log n)** sort with **O(1) extra space**, and the heap it builds is the engine behind priority queues.

| Problem | Concept Used |
|---------|--------------|
| Kth Largest Element in an Array | Heap |
| Top K Frequent Elements | Heap + hashing |
| Merge K Sorted Lists | Min-heap |
| Find Median from Data Stream | Two heaps |
| Sort an Array | Sorting algorithms |

---

## Contributing

Contributions are welcome! Fork the repository, create a feature branch, and open a pull request with a short description of the change.

---

## License

This project is licensed under the MIT License.