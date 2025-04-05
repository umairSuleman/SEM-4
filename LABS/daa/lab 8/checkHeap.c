#include <stdio.h>
#include <stdbool.h>

// Function to check if the array is a Min Heap
bool isMinHeap(int H[], int n) {
    for (int i = 1; i <= n / 2; i++) { // Only check internal nodes
        int left = 2 * i;      // Left child index
        int right = 2 * i + 1; // Right child index

        if (left <= n && H[i] > H[left]) return false; // Parent should be ≤ left child
        if (right <= n && H[i] > H[right]) return false; // Parent should be ≤ right child
    }
    return true;
}

// Function to check if the array is a Max Heap
bool isMaxHeap(int H[], int n) {
    for (int i = 1; i <= n / 2; i++) { // Only check internal nodes
        int left = 2 * i;
        int right = 2 * i + 1;

        if (left <= n && H[i] < H[left]) return false; // Parent should be ≥ left child
        if (right <= n && H[i] < H[right]) return false; // Parent should be ≥ right child
    }
    return true;
}

// Function to determine whether it's a heap and which type
void checkHeapType(int H[], int n) {
    if (isMinHeap(H, n)) {
        printf("The array is a Min Heap.\n");
    } else if (isMaxHeap(H, n)) {
        printf("The array is a Max Heap.\n");
    } else {
        printf("The array is NOT a Heap.\n");
    }
}

// Main function
int main() {
    int H[] = {0, 10, 20, 30, 40, 50, 60}; // 1-based index, ignore H[0]
    int n = sizeof(H) / sizeof(H[0]) - 1; // Since index 0 is not used

    printf("Checking if the array is a heap...\n");
    checkHeapType(H, n);

    return 0;
}
