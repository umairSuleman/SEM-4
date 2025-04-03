#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASH_SIZE 13

typedef struct hash {
    char *table[HASH_SIZE];
} hash;

void initHashTable(hash *ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

int hashFunction(hash *ht, char *key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (isalpha(c)) {
            sum += (c - 'A' + 1);
        }
    }
    return sum % HASH_SIZE;
}

void insert(hash *ht, char *key) {
    int index = hashFunction(ht, key);
    int original_index = index;

    while (ht->table[index] != NULL) {
        index = (index + 1) % HASH_SIZE;
        if (index == original_index) {
            printf("Hash table is FULL.\n");
            return;
        }
    }
    ht->table[index] = strdup(key);
}

void printHash(hash *ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("[%2d]: ", i);
        if (ht->table[i] == NULL) {
            printf("NULL");
        } else {
            printf("%s", ht->table[i]);
        }
        printf("\n");
    }
}

void freeHashTable(hash *ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (ht->table[i] != NULL) {
            free(ht->table[i]);
        }
    }
}

int main() {
    int num;
    printf("Enter the number of keys: ");
    scanf("%d", &num);

    char keys[num][50];

    printf("Enter keys:\n");
    for (int i = 0; i < num; i++) {
        scanf("%49s", keys[i]);
    }

    hash ht;
    initHashTable(&ht);

    for (int i = 0; i < num; i++) {
        insert(&ht, keys[i]);
    }

    printHash(&ht);
    freeHashTable(&ht);

    return 0;
}
