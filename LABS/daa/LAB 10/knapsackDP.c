#include <stdio.h>

void findSubset(int n, int maxCap, int dp[n+1][maxCap+1], int p[], int w[]) {        //imp to declare indices first since VLA
    int res = dp[n][maxCap];
    int remainingCap = maxCap;
    printf("Optimal subset:\n");

    for (int i = n; i > 0 && res > 0; i--) {
        if (res == dp[i-1][remainingCap]) {                                           //if value alr above then skip
            continue;
        } else {
            printf("Item %d (profit: %d, weight: %d)\n", i, p[i-1], w[i-1]);           //else value must hbe included
            res -= p[i-1];
            remainingCap -= w[i-1];
        }
    }
}

// Function to return the maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve 0/1 Knapsack using Dynamic Programming
int knapsackDP(int p[], int w[], int maxCap, int n) {
    int dp[n+1][maxCap+1];  // DP table

    // Build the DP table
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= maxCap; j++) {  
            // Base case: No items or capacity is 0
            if (i == 0 || j == 0) {
                dp[i][j] = 0;  
            }
            // If the current item's weight is within capacity
            else if (j >= w[i-1]) {  
                dp[i][j] = max(dp[i-1][j], p[i-1] + dp[i-1][j - w[i-1]]);
            }
            // Exclude the item
            else {
                dp[i][j] = dp[i-1][j];  
            }
        }
    }

    for(int i=0; i<=n; i++){
        for(int j=0; j<=maxCap; j++){
            printf("%d\t", dp[i][j]);
        }
        printf("\n");
    }

    findSubset(n, maxCap, dp, p, w);

    return dp[n][maxCap];  // Return the maximum profit
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int profits[n], weights[n], maxCap;

    printf("Enter the weights of the objects: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    printf("Enter the profits of the objects: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &profits[i]);
    }

    printf("Enter the maximum capacity: ");
    scanf("%d", &maxCap);

    int result = knapsackDP(profits, weights, maxCap, n);

    printf("Maximised Profit: %d\n", result);
    return 0;  
}
