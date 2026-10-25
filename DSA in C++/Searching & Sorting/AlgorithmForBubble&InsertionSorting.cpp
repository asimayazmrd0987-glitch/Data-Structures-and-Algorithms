Bubble Sort Algorithm
BubbleSort(A):
    n = length(A)
    for i = 0 to n - 1:
        swapped = false
        for j = 0 to n - i - 2:
            if A[j] > A[j + 1]:
                swap(A[j], A[j + 1])
                swapped = true
        if not swapped:
            break





Insertion Sort Algorithm
InsertionSort(A):
    n = length(A)
    for i = 1 to n - 1:
        key = A[i]
        j = i - 1
        while j >= 0 and A[j] > key:
            A[j + 1] = A[j]
            j = j - 1
        A[j + 1] = key
