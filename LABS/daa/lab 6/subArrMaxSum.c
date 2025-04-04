#include<stdio.h>
#include<limits.h>


int max(int a, int b, int c){
    return c>(a>b?a:b)?c:(a>b?a:b);
}

int crossOver(int arr[], int low, int mid, int hi){

    int lSum=INT_MIN;
    int rSum=INT_MIN;

    //calculate left sum
    int sum=0;
    for(int i=mid; i>=low; i--){
        sum += arr[i];
        if(sum>lSum){
            lSum=sum;
        }
    }

    //calculate right sum
    sum=0;
    for(int i=mid+1; i<=hi; i++){
        sum += arr[i];
        if(sum>rSum){
            rSum=sum;
        }
    }

    //crossover sum
    return lSum+rSum;

}

int maxSum(int arr[], int low, int hi){
    if(low==hi){
        return arr[hi];         //base case
    }

    int mid=(low+hi)/2;

    return max(
        maxSum(arr, low, mid),
        maxSum(arr, mid+1, hi),
        crossOver(arr,low, mid, hi)
    );
}

int main(){
    int n;
    printf("Enter size of arr:");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements:");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    int val=maxSum(arr, 0, n-1);

    printf("Value:%d", val);
}
