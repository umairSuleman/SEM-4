#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Preprocess the Bad Character Shift Table using Horspool's method
void preprocess_bad_character(const char *pattern, int m, int *bad_char) {
    for (int i = 0; i < 256; i++) {
        bad_char[i] = m; // Default shift is the pattern length
    }
    for (int j = 0; j < m - 1; j++) {
        bad_char[(unsigned char)pattern[j]] = m - 1 - j;
    }
}

// Preprocess the Good Suffix Table based on the specified rules
void preprocess_good_suffix(const char *pattern, int m, int *good_suffix) {
    // Initialize all entries to m (pattern length)
    for (int k = 0; k < m; k++) {
        good_suffix[k] = m;
    }

    for (int k = 1; k < m; k++) { // k is the length of the suffix
        const char *suffix = pattern + (m - k);
        int found = -1;

        // Look for the rightmost occurrence of the suffix not preceded by the same character
        for (int i = 0; i <= m - k - 1; i++) {
            if (memcmp(pattern + i, suffix, k) == 0) {
                if (i == 0) {
                    found = i; // No preceding character, valid
                } else {
                    char original_pre = pattern[m - k - 1];
                    char current_pre = pattern[i - 1];
                    if (original_pre != current_pre) {
                        found = i; // Preceding characters differ, valid
                    }
                }
            }
        }

        if (found != -1) {
            good_suffix[k] = (m - k) - found;
        } else {
            // Find the longest prefix of length l < k that matches a suffix
            int max_l = 0;
            for (int l = k - 1; l >= 1; l--) {
                if (memcmp(pattern, pattern + (m - l), l) == 0) {
                    max_l = l;
                    break;
                }
            }
            good_suffix[k] = m - max_l;
        }
    }
}

// Boyer-Moore algorithm with the specified conditions
int boyer_moore(const char *pattern, const char *text) {
    int m = strlen(pattern);
    int n = strlen(text);

    if (m == 0 || n == 0 || m > n) return -1;

    int bad_char[256];
    preprocess_bad_character(pattern, m, bad_char);

    int *good_suffix = (int *)malloc(m * sizeof(int));
    preprocess_good_suffix(pattern, m, good_suffix);

    // Print Bad Character Shift Table
    printf("Bad Character Shift Table:\n");
    for (int i = 0; i < 256; i++) {
        if (bad_char[i] != m) {
            if (i == ' ') {
                printf("' ': %d\n", bad_char[i]);
            } else if (i == '_') {
                printf("'_': %d\n", bad_char[i]);
            } else if (i >= 32 && i <= 126) { // Printable ASCII characters
                printf("'%c': %d\n", (char)i, bad_char[i]);
            }
        }
    }
    printf("\n");

    // Print Good Suffix Table
    printf("Good Suffix Table:\n");
    for (int k = 1; k < m; k++) {
        printf("k = %d: shift = %d\n", k, good_suffix[k]);
    }
    printf("\n");

    int i = m - 1; // Current end of pattern alignment in text

    while (i < n) {
        int k = 0;
        // Determine the number of matched characters k
        while (k < m && pattern[m - 1 - k] == text[i - k]) {
            k++;
        }

        if (k == m) {
            free(good_suffix);
            return i - m + 1; // Match found
        } else {
            int d1 = bad_char[(unsigned char)text[i - k]]-k;
            int d2 = good_suffix[k];
            int shift = (d1 > d2) ? d1 : d2;
            // Ensure at least a shift of 1 to prevent infinite loops
            if (shift == 0) shift = 1;
            i += shift;
        }
    }

    free(good_suffix);
    return -1; // No match found
}

int main() {
    const char *text = "BESSY KNEW ABOUT BAOBABS";
    const char *pattern = "BAOBAB";

    int result = boyer_moore(pattern, text);

    if (result != -1) {
        printf("Pattern found at index: %d\n", result);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}
