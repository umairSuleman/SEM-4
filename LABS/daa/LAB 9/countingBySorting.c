#include<stdio.h>

void main(){
    int n;

    printf("Enter the size of the array:");
    scanf("%d", &n);

    int arr[n], s[n], count[n];

    printf("Enter array elements:");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
        count[i]=0;
    }

    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(arr[i]<arr[j]){
                count[j]+=1;
            }
            else{
                count[i]+=1;
            }
        }
    }

    for(int i=0; i<n; i++){
        s[count[i]]=arr[i];
    }

    printf("Ordered Array:\n");

    for(int i=0; i<n; i++){
        printf("%d\t", s[i]);
    }
}
