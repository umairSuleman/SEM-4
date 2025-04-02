#include <stdio.h>
#include <string.h>

void shift_table(const char *pattern, int m, int *table) {
    // Initialize all entries with pattern length
    for (int i = 0; i < 256; i++) {
        table[i] = m;
    }
    
    // Fill shifts for characters in pattern (except last character)
    for (int j = 0; j < m - 1; j++) {
        table[(unsigned char)pattern[j]] = m - 1 - j;
    }
}

int horspool_matching(const char *pattern, const char *text) {
    int m = strlen(pattern);
    int n = strlen(text);
    
    // Handle edge cases
    if (m == 0 || n == 0 || m > n) return -1;
    
    int table[256];
    shift_table(pattern, m, table);
    
    int i = m - 1;  // Position of pattern's right end in text
    
    while (i < n) {
        int k = 0;
        // Compare from end of pattern backwards
        while (k < m && pattern[m - 1 - k] == text[i - k]) {
            k++;
        }
        
        if (k == m) {
            return i - m + 1;  // Full match found
        } else {
            // Shift using the current text character's table value
            i += table[(unsigned char)text[i]];
        }
    }
    
    return -1;  // No match found
}

int main() {
    const char *text = "ABABABACABCABAB";
    const char *pattern = "ABAB";
    
    int result = horspool_matching(pattern, text);
    
    if (result != -1) {
        printf("Pattern found at index: %d\n", result);
    } else {
        printf("Pattern not found\n");
    }
    
    return 0;
}
