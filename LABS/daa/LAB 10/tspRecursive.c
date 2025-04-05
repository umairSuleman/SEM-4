#include <stdio.h>
#include <limits.h>

#define N 4 // Number of cities
#define VISITED_ALL (1 << N) - 1 // Bitmask representing all cities visited (e.g., 1111 for N=4)

int tsp(int graph[N][N], int mask, int pos, int dp[N][1 << N]) {
    if (mask == VISITED_ALL) {
        return graph[pos][0]; // Return to starting city
    }
    if (dp[pos][mask] != -1) {
        return dp[pos][mask]; // Return cached result
    }

    int min_cost = INT_MAX;
    for (int city = 0; city < N; city++) {
        if (!(mask & (1 << city))) { // If city not visited
            int new_cost = graph[pos][city] + tsp(graph, mask | (1 << city), city, dp);
            if (new_cost < min_cost) {
                min_cost = new_cost;
            }
        }
    }
    return dp[pos][mask] = min_cost; // Cache and return
}

int main() {
    int graph[N][N] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int dp[N][1 << N]; // DP table: [current_city][bitmask]
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < (1 << N); j++) {
            dp[i][j] = -1; // Initialize to -1 (unvisited)
        }
    }

    printf("Minimum TSP cost: %d\n", tsp(graph, 1, 0, dp)); // Start at city 0 (bitmask 0001)
    return 0;
}
