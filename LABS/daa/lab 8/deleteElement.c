#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function for Min Heap
void minHeapify(int heap[], int n, int i) {
    int smallest = i;  
    int left = 2 * i;  
    int right = 2 * i + 1; 

    if (left <= n && heap[left] < heap[smallest])
        smallest = left;

    if (right <= n && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

// Function to delete an element from the heap
void deleteElement(int heap[], int *n, int value) {
    int i;
    for (i = 1; i <= *n; i++) {
        if (heap[i] == value)
            break;
    }

    // If element is not found
    if (i > *n) {
        printf("Element %d not found in the heap.\n", value);
        return;
    }

    // Replace the element with the last element
    heap[i] = heap[*n];
    (*n)--;  // Reduce heap size

    // Heapify to restore the heap property
    minHeapify(heap, *n, i);

    printf("Element %d deleted successfully.\n", value);
}

// Function to print the heap
void printHeap(int heap[], int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

// Main function
int main() {
    int heap[] = {0, 10, 20, 30, 40, 50, 60};  // 1-based indexing
    int n = sizeof(heap) / sizeof(heap[0]) - 1; // Ignore heap[0]

    printf("Original Heap:\n");
    printHeap(heap, n);

    int value;
    printf("Enter value to delete: ");
    scanf("%d", &value);

    deleteElement(heap, &n, value);

    printf("Heap after deletion:\n");
    printHeap(heap, n);

    return 0;
}
