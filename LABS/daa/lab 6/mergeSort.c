#include <stdio.h>
#include <stdlib.h>

// Function to merge two halves and count inversions
void merge(int brr[], int crr[], int arr[], int p, int q, int n, int *inv_count) {
    int i = 0, j = 0, k = 0;

    while (i < p && j < q) {
        if (brr[i] <= crr[j]) {
            arr[k] = brr[i];
            i++;
        } else {
            arr[k] = crr[j];
            j++;
            // If crr[j] is smaller than brr[i], then all remaining elements in brr[i..p-1] are greater than crr[j]
            // So, the number of inversions is (p - i)
            *inv_count += (p - i);
        }
        k++;
    }

    // Copy the remaining elements of brr[], if any
    while (i < p) {
        arr[k] = brr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of crr[], if any
    while (j < q) {
        arr[k] = crr[j];
        j++;
        k++;
    }
}

// Function to perform merge sort and count inversions
void mergesort(int arr[], int n, int *inv_count) {
    if (n > 1) {
        int brr[n / 2];
        int crrsize = n - n / 2;  // Correct size for the second half
        int crr[crrsize];

        for (int i = 0; i < n / 2; i++) {
            brr[i] = arr[i];
        }

        int j = 0;
        for (int i = n / 2; i < n; i++) {
            crr[j] = arr[i];
            j++;
        }

        // Recursively sort and count inversions in the left and right subarrays
        mergesort(brr, n / 2, inv_count);
        mergesort(crr, crrsize, inv_count);

        // Merge the two subarrays and count inversions during the merge step
        merge(brr, crr, arr, n / 2, crrsize, n, inv_count);
    }
}

int main() {
    int arr[100], size;

    printf("Enter size of array: ");
    scanf("%d", &size);

    printf("Enter elements:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    int inv_count = 0;

    // Call mergesort and get the inversion count
    mergesort(arr, size, &inv_count);

    printf("After Sorting:\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t", arr[i]);
    }

    printf("\nTotal Inversions: %d\n", inv_count);

    return 0;  // Return 0 to indicate successful execution
}
