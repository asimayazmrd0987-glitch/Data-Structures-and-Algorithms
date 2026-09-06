# Data Structures & Algorithms — Python Roadmap

Structured DSA roadmap in Python, run alongside a parallel C++ track (CS-201 coursework) and used for FAANG-style interview prep. Same topic order as the C++ side — the aim here is **Python fluency for DSA**, not relearning concepts from scratch.

**Approach:** implement each structure raw first (no `collections`/`heapq` shortcuts), then reinforce with 3–5 LeetCode problems, easy → medium, before moving on.

---

## Progress Tracker

- [ ] Phase 0 — Python for DSA
- [ ] Phase 1 — Complexity Analysis
- [ ] Phase 2 — Arrays & Strings
- [ ] Phase 3 — Recursion
- [ ] Phase 4 — Linked Lists
- [ ] Phase 5 — Stacks & Queues
- [ ] Phase 6 — Trees
- [ ] Phase 7 — Hashing
- [ ] Phase 8 — Heaps / Priority Queues
- [ ] Phase 9 — Graphs
- [ ] Phase 10 — Dynamic Programming
- [ ] Phase 11 — Sorting & Searching (dedicated)
- [ ] Phase 12 — Greedy & Backtracking

---

## Phase 0 — Python for DSA (don't skip this)

Python hides a lot of complexity behind clean syntax — know what's actually happening underneath before you rely on it.

- [ ] Lists vs arrays: Python lists are dynamic arrays — know when `append` is O(1) amortized vs when list operations are O(n)
- [ ] Slicing (`arr[1:3]`, `arr[::-1]`) — know it creates a **copy**, not a view (memory cost)
- [ ] Tuples vs lists — immutability and when to use which
- [ ] Dictionaries — average O(1) lookup, how hashing works under the hood
- [ ] Sets — O(1) membership check, use for dedup/lookup problems
- [ ] String immutability — why repeated concatenation in a loop is O(n²), and the fix (`''.join()`)
- [ ] List comprehensions — readable, often faster than manual loops
- [ ] `collections` module: `deque`, `defaultdict`, `Counter` (learn these *after* you've built stacks/queues raw once)
- [ ] `heapq` module (min-heap only — know the trick for max-heap using negation)
- [ ] `bisect` module for binary search on sorted lists

---

## Phase 1 — Complexity Analysis

- [ ] Big-O, Big-Theta, Big-Omega — what each actually describes
- [ ] Time complexity of common Python operations (list append/insert/pop, dict get/set, `in` on list vs set)
- [ ] Space complexity — recognize recursion's hidden stack space cost early

---

## Phase 2 — Arrays & Strings

- [ ] Traversal, insertion, deletion basics
- [ ] Two-pointer technique
- [ ] Sliding window (fixed and variable size)
- [ ] Prefix sums
- [ ] Kadane's algorithm (max subarray)
- [ ] String manipulation: reversal, palindrome check, anagram check
- [ ] **Practice:** 5 problems (Two Sum, Best Time to Buy/Sell Stock, Valid Anagram, Longest Substring Without Repeating Characters, Product of Array Except Self)

---

## Phase 3 — Recursion

- [ ] Base case + recursive case, tracing the call stack by hand
- [ ] Recursion vs iteration — when each is more natural
- [ ] Backtracking basics (subsets, permutations) — light intro, deep dive comes in Phase 12
- [ ] Memoization intro (sets up Phase 10)
- [ ] **Practice:** 4 problems (Fibonacci, Factorial, Power function, Reverse a string recursively)

---

## Phase 4 — Linked Lists

- [ ] Build a singly linked list **from scratch** (Node class, no shortcuts)
- [ ] Traversal, insertion, deletion (head/tail/middle)
- [ ] Reverse a linked list (iterative + recursive)
- [ ] Detect a cycle (Floyd's slow/fast pointer)
- [ ] Doubly linked list (know the concept, implement if time allows)
- [ ] **Practice:** 4 problems (Reverse Linked List, Merge Two Sorted Lists, Linked List Cycle, Middle of Linked List)

---

## Phase 5 — Stacks & Queues

- [ ] Implement a stack raw (using a Python list)
- [ ] Implement a queue raw (naive list-based, then see why `deque` exists)
- [ ] Valid parentheses / balanced brackets
- [ ] Monotonic stack pattern (intro)
- [ ] **Practice:** 4 problems (Valid Parentheses, Min Stack, Implement Queue using Stacks, Daily Temperatures)

---

## Phase 6 — Trees

- [ ] Binary tree basics: Node class, insertion
- [ ] Traversals: inorder, preorder, postorder (recursive, then iterative with an explicit stack)
- [ ] BFS / level-order traversal (using a queue)
- [ ] Binary Search Tree (BST): insert, search, delete
- [ ] Tree height, balanced check
- [ ] Lowest Common Ancestor
- [ ] (Know they exist, don't obsess): AVL rotations, Red-Black trees
- [ ] **Practice:** 5 problems (Max Depth of Binary Tree, Validate BST, Level Order Traversal, Invert Binary Tree, LCA of BST)

---

## Phase 7 — Hashing

- [ ] How Python dicts/sets work under the hood (hash function, collisions)
- [ ] Hash map for O(1) lookup patterns — this pattern alone solves a huge chunk of "easy" interview questions
- [ ] Frequency counting (`Counter`, or raw dict)
- [ ] Two-sum style problems using a hash map instead of brute force
- [ ] **Practice:** 4 problems (Two Sum, Group Anagrams, Longest Consecutive Sequence, Contains Duplicate)

---

## Phase 8 — Heaps / Priority Queues

- [ ] What a heap guarantees (min-heap: parent ≤ children)
- [ ] `heapq` module: `heappush`, `heappop`, `heapify`
- [ ] Max-heap trick in Python (push negated values)
- [ ] Kth largest/smallest element pattern
- [ ] **Practice:** 3 problems (Kth Largest Element, Top K Frequent Elements, Merge K Sorted Lists)

---

## Phase 9 — Graphs

- [ ] Representations: adjacency list vs adjacency matrix
- [ ] BFS and DFS (both iterative and recursive DFS)
- [ ] Detect cycle (directed and undirected)
- [ ] Topological sort
- [ ] Union-Find / Disjoint Set (intro)
- [ ] Dijkstra's algorithm (intro — shortest path)
- [ ] **Practice:** 5 problems (Number of Islands, Clone Graph, Course Schedule, Pacific Atlantic Water Flow, Graph Valid Tree)

---

## Phase 10 — Dynamic Programming (the hard one — go slow here)

- [ ] Identify DP problems: overlapping subproblems + optimal substructure
- [ ] Top-down (memoization) vs bottom-up (tabulation)
- [ ] 1D DP: Climbing Stairs, House Robber
- [ ] 2D DP: Unique Paths, Longest Common Subsequence
- [ ] Knapsack pattern (0/1 knapsack)
- [ ] **Practice:** 6 problems (Climbing Stairs, House Robber, Coin Change, Longest Increasing Subsequence, Unique Paths, Edit Distance)

---

## Phase 11 — Sorting & Searching (dedicated pass)

- [ ] Implement raw: bubble, selection, insertion sort (understand, don't over-invest)
- [ ] Implement raw: merge sort, quicksort (these matter — know time/space tradeoffs)
- [ ] Binary search — and all its variants (first/last occurrence, search in rotated sorted array)
- [ ] Python's built-in `sorted()` / `.sort()` — Timsort, when to just use it vs implement your own

---

## Phase 12 — Greedy & Backtracking

- [ ] Greedy: when local optimal choices lead to global optimal (and when they don't)
- [ ] Backtracking template: choose → explore → un-choose
- [ ] Subsets, permutations, combinations (revisit from Phase 3, go deeper)
- [ ] N-Queens as the classic backtracking problem
- [ ] **Practice:** 4 problems (Subsets, Permutations, Combination Sum, N-Queens)

---

## Notes

- This roadmap intentionally matches the order used in the parallel C++ track — same concepts, different syntax, so neither track has to re-learn logic the other already covers.
- Interview-critical topics (per target companies — Google/Meta/Microsoft): Arrays/Strings, Trees, Graphs, DP, Hashing. Weight practice time accordingly.
- Each phase's practice problems are a floor, not a ceiling — more reps on weak topics, fewer on ones that click fast.
