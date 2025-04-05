#include <stdio.h>

void heapify(int heap[], int n, int i) {
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= n && heap[left] > heap[largest])
        largest = left;
    
    if (right <= n && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        heapify(heap, n, largest);
    }
}

// Function to find the smallest element in the max heap
int findSmallest(int heap[], int n) {
    int minIdx = n / 2 + 1; // First leaf node
    int minValue = heap[minIdx];

    for (int i = minIdx + 1; i <= n; i++) {
        if (heap[i] < minValue) {
            minValue = heap[i];
            minIdx = i;
        }
    }

    return minIdx; // Return index of the smallest element
}

// Function to delete the smallest element in the max heap
void deleteSmallest(int heap[], int *n) {
    if (*n == 0) {
        printf("Heap is empty!\n");
        return;
    }

    int minIdx = findSmallest(heap, *n);
    printf("Deleting smallest element: %d\n", heap[minIdx]);

    // Replace smallest element with last element in heap
    heap[minIdx] = heap[*n];
    (*n)--;

    // Heapify down if necessary
    heapify(heap, *n, minIdx);
}

// Function to print the heap
void printHeap(int heap[], int n) {
    printf("Heap: ");
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main() {
    int heap[] = {0, 50, 30, 40, 10, 20, 5}; // Index 0 is ignored
    int n = 6; // Number of elements

    printf("Original Max Heap:\n");
    printHeap(heap, n);

    deleteSmallest(heap, &n);

    printf("Heap after deletion:\n");
    printHeap(heap, n);

    return 0;
}
