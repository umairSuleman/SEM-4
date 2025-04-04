#include <stdio.h>
#include <stdlib.h>

// Function to return the maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Global DP table (initialized with -1)
int **V;

// Memory Function Knapsack (Top-Down with Memoization)
int MFKnapsack(int i, int j, int weights[], int values[]) {
    // If the result is already computed, return it
    if (V[i][j] >= 0) 
        return V[i][j];

    int value;
    
    // Base Case: No items or zero capacity
    if (i == 0 || j == 0) 
        value = 0;
    else if (j < weights[i-1])  
        value = MFKnapsack(i-1, j, weights, values);  // Skip item if it doesn't fit
    else  
        value = max(MFKnapsack(i-1, j, weights, values), 
                    values[i-1] + MFKnapsack(i-1, j - weights[i-1], weights, values));

    // Store computed result
    V[i][j] = value;
    
    return value;
}

// Function to find the optimal subset of items
void findSubset(int n, int maxCap, int weights[], int values[]) {
    int res = V[n][maxCap];  // Optimal profit value
    int remainingCap = maxCap;

    printf("Optimal subset:\n");

    for (int i = n; i > 0 && res > 0; i--) {
        // If the item is not included in the optimal subset
        if (res == V[i-1][remainingCap]) {
            continue;
        } else {
            // Item is included
            printf("Item %d (profit: %d, weight: %d)\n", i, values[i-1], weights[i-1]);
            res -= values[i-1];
            remainingCap -= weights[i-1];
        }
    }
}

int main() {
    int n, maxCap;
    
    printf("Enter the number of items: ");
    scanf("%d", &n);

    int weights[n], values[n];

    printf("Enter the weights of the items: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    printf("Enter the profits/values of the items: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    printf("Enter the maximum knapsack capacity: ");
    scanf("%d", &maxCap);

    // Allocate memory for DP table and initialize with -1
    V = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        V[i] = (int *)malloc((maxCap + 1) * sizeof(int));
        for (int j = 0; j <= maxCap; j++) {
            V[i][j] = -1;
        }
    }

    // Compute the optimal knapsack solution
    int maxProfit = MFKnapsack(n, maxCap, weights, values);
    printf("Maximized Profit: %d\n", maxProfit);

    // Find the optimal subset of items
    findSubset(n, maxCap, weights, values);

    // Free allocated memory
    for (int i = 0; i <= n; i++) {
        free(V[i]);
    }
    free(V);

    return 0;
}
