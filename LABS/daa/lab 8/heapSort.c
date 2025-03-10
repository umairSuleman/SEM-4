#include <stdio.h>
#include <stdbool.h>

void bottomUpHeap(int arr[], int n) {
    for (int i = (n - 1) / 2; i >= 0; i--) {
        int k = i;
        int v = arr[k];
        bool heap = false;

        while (!heap && (2 * k + 1) < n) {
            int j = 2 * k + 1;  // Left child

            if (j + 1 < n && arr[j] < arr[j + 1]) { // Right child exists and is greater
                j++;
            }

            if (v >= arr[j]) {
                heap = true;
            } else {
                arr[k] = arr[j];
                k = j;
            }
        }
        arr[k] = v;
    }
}

void heapsort(int arr[], int n) {

    for (int i = n - 1; i > 0; i--) {  
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        bottomUpHeap(arr, i);  
    }
}

int main() {  
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    bottomUpHeap(arr,n);
    printf("Heap: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    heapsort(arr, n);

    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
