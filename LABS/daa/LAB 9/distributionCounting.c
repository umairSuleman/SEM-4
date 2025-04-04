#include<stdio.h>

void distributionCounting(int arr[], int n, int l, int u){

    int S[n];                   //reult array
    int numOfElements=u-l+1;       // number of elements

    int D[numOfElements];       //Distribution Value array

    // Initialise all values to zero
    for(int i=0; i<numOfElements; i++){
        D[i]=0;
    }

    //Computing frequencies
    for(int i=0; i<n; i++){
        D[arr[i]-l] += 1;
    }

    //Computing distribution values
    for(int i=0; i<numOfElements; i++){
        if(i==0){
            continue;
        }
        else{
            D[i]=D[i-1]+D[i]; //prev element D value + curr element freq value 
        }
    }

    for(int i=n-1; i>=0; i--){
        int j= arr[i]-l;        //obtains position
        S[D[j]-1]=arr[i];
        D[j]--;                  //decrement for next position
    }

    printf("Sorrted Array:");
    for(int i=0; i<n; i++)
        printf("%d\t", S[i]);

    printf("\n");
}

void main(){

    int n; 
    printf("Enter number of elements:");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements:");
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);

    int l, u; 
    printf("Enter upper and lower limit:");
    scanf("%d %d", &u, &l);

    distributionCounting(arr, n, l, u);
}
