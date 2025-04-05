#include <stdio.h>
#include <limits.h>

#define N 3 // Number of jobs/workers

int assignment(int cost[N][N], int mask, int worker, int dp[N][1 << N]) {
    if (worker == N) {
        return 0; // All workers assigned
    }
    if (dp[worker][mask] != -1) {
        return dp[worker][mask]; // Return cached result
    }

    int min_cost = INT_MAX;
    for (int job = 0; job < N; job++) {
        if (!(mask & (1 << job))) { // If job not assigned
            int new_cost = cost[worker][job] + assignment(cost, mask | (1 << job), worker + 1, dp);
            if (new_cost < min_cost) {
                min_cost = new_cost;
            }
        }
    }
    return dp[worker][mask] = min_cost; // Cache and return
}

int main() {
    int cost[N][N] = {
        {2, 3, 1},
        {5, 4, 8},
        {7, 2, 6}
    };

    int dp[N][1 << N]; // DP table: [worker][bitmask]
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < (1 << N); j++) {
            dp[i][j] = -1; // Initialize to -1 (unvisited)
        }
    }

    printf("Minimum assignment cost: %d\n", assignment(cost, 0, 0, dp)); // Start with worker 0, no jobs assigned
    return 0;
}
