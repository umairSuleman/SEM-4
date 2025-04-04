#include<stdio.h>
#include<stdlib.h>

int partition(int arr[], int lo, int hi);

void quicksort(int arr[], int lo, int hi){
    if(lo >= hi || lo < 0)
        return;

    int s = partition(arr, lo, hi); // Get the pivot index
    quicksort(arr, lo, s - 1);     // Sort the left subarray
    quicksort(arr, s + 1, hi);     // Sort the right subarray
}

int partition(int arr[], int lo, int hi){
    int p = arr[lo]; // Pivot element
    int i = lo, j = hi + 1;

    do{
        // Increment i while arr[i] < p
        do{
            i++;
        } while(arr[i]<= p && i < hi);

        do{
            j--;
        }while(arr[j]>=p && j>lo);

        // Swap arr[i] and arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }while(i<j);

    //undo last swap
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;

    // Swap pivot (arr[lo]) with arr[j]
    temp = arr[lo];
    arr[lo] = arr[j];
    arr[j] = temp;

    return j; // Return the pivot index
}

int main(){
    int arr[100], size;

    printf("Enter size of array: ");
    scanf("%d", &size);

    printf("Enter elements:\n");
    for(int i = 0; i < size; i++){
        scanf("%d", &arr[i]);
    }

    quicksort(arr, 0, size - 1);

    printf("After Sorting:\n");
    for(int i = 0; i < size; i++){
        printf("%d\t", arr[i]);
    }

    return 0;
}
