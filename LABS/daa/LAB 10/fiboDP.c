#include <stdio.h>

//Uses DP
int fibarr(int n) {
    if (n <= 1)
        return n;

    int dp[n + 1];  // Array to store Fibonacci numbers
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];

    return dp[n];
}

//More space efficient
int fibNoArray(int n) {
    if (n <= 1)
        return n;

    int a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }

    return b;
}
