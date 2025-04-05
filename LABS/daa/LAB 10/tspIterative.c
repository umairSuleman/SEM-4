#include <stdio.h>
#include <limits.h>

#define N 3  // Number of jobs/workers

int assignment_iterative(int cost[N][N]) {
    int dp[1 << N];  // dp[mask] = min cost for job assignments in mask
    
    // Initialize DP table with infinity
    for (int mask = 0; mask < (1 << N); mask++) {
        dp[mask] = INT_MAX;
    }
    
    // Base case: no jobs assigned (cost = 0)
    dp[0] = 0;
    
    // Iterate over all subsets of jobs
    for (int mask = 0; mask < (1 << N); mask++) {
        if (dp[mask] == INT_MAX) continue;  // Skip unreachable states
        
        // Count assigned jobs (worker index)
        int worker = __builtin_popcount(mask);
        
        // Try assigning each unassigned job to the current worker
        for (int job = 0; job < N; job++) {
            if (!(mask & (1 << job))) {  // If job not assigned
                int new_mask = mask | (1 << job);
                int new_cost = dp[mask] + cost[worker][job];
                
                if (new_cost < dp[new_mask]) {
                    dp[new_mask] = new_cost;
                }
            }
        }
    }
    
    return dp[(1 << N) - 1];  // All jobs assigned
}

int main() {
    int cost[N][N] = {
        {2, 3, 1},
        {5, 4, 8},
        {7, 2, 6}
    };
    
    printf("Minimum assignment cost (iterative): %d\n", assignment_iterative(cost));
    return 0;
}
