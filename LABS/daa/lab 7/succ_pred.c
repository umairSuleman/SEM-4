#include<stdio.h>
#include "AVL.h"

struct Node* leftmostNode(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Function to find the rightmost node (maximum value in a subtree)
struct Node* rightmostNode(struct Node* node) {
    while (node->right != NULL)
        node = node->right;
    return node;
}

// Function to find the successor of a given key
struct Node* successor(struct Node* root, int key) {
    struct Node* current = root;
    struct Node* succ = NULL;

    while (current != NULL) {
        if (key < current->key) {
            succ = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return succ;
}

// Function to find the predecessor of a given key
struct Node* predecessor(struct Node* root, int key) {
    struct Node* current = root;
    struct Node* pred = NULL;

    while (current != NULL) {
        if (key > current->key) {
            pred = current;
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return pred;
}

int main() {
    struct Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("In-order traversal of the AVL tree:\n");
    inOrder(root);
    printf("\n");

    int key = 30;
    struct Node* succ = successor(root, key);
    struct Node* pred = predecessor(root, key);

    if (succ != NULL)
        printf("Successor of %d is %d\n", key, succ->key);
    else
        printf("No successor found for %d\n", key);

    if (pred != NULL)
        printf("Predecessor of %d is %d\n", key, pred->key);
    else
        printf("No predecessor found for %d\n", key);

    return 0;
}
