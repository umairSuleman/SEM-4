#include <stdio.h>
#include <stdbool.h>

void bottomUpHeap(int arr[], int n) {
    for (int i = (n - 1) / 2; i >= 0; i--) {
        int p_pos = i;
        int p_val = arr[p_pos];
        bool heap = false;

        while (!heap && (2 * p_pos + 1) < n) {
            int c_pos = 2 * p_pos + 1;  // Left child

            if (c_pos + 1 < n && arr[c_pos] < arr[c_pos + 1]) { // Right child exists and is greater
                c_pos++;                //c_pos now holds larger child
            }

            if (p_val >= arr[c_pos]) {        //if parent > child then heap is true
                heap = true;
            } else {
                arr[p_pos] = arr[c_pos];            //else move child to parent position
                p_pos = c_pos;                       //save parents new position in childs old position
            }
        }
        arr[p_pos] = p_val;                        //move parent to its new position
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
