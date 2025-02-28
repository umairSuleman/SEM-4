#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the AVL tree
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Function to get the height of a node
int height(struct Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is initially added at leaf
    return node;
}

// Function to right rotate subtree rooted with y
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get the balance factor of a node
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a key iteratively into the AVL tree
struct Node* insert(struct Node* root, int key) {
    struct Node* current = root;
    struct Node* parent = NULL;
    struct Node** path = (struct Node**)malloc(100 * sizeof(struct Node*));
    int top = -1;

    // Standard BST insertion
    while (current != NULL) {
        path[++top] = current;
        parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    struct Node* newNodePtr = newNode(key);
    if (parent == NULL) {
        root = newNodePtr;
    } else if (key < parent->key) {
        parent->left = newNodePtr;
    } else {
        parent->right = newNodePtr;
    }

    // Update heights and balance the tree
    while (top >= 0) {
        current = path[top--];
        current->height = 1 + max(height(current->left), height(current->right));

        int balance = getBalance(current);

        // Left Left Case
        if (balance > 1 && key < current->left->key)
            current = rightRotate(current);

        // Right Right Case
        if (balance < -1 && key > current->right->key)
            current = leftRotate(current);

        // Left Right Case
        if (balance > 1 && key > current->left->key) {
            current->left = leftRotate(current->left);
            current = rightRotate(current);
        }

        // Right Left Case
        if (balance < -1 && key < current->right->key) {
            current->right = rightRotate(current->right);
            current = leftRotate(current);
        }

        // Update the parent pointer
        if (top >= 0) {
            if (path[top]->left == current)
                path[top]->left = current;
            else
                path[top]->right = current;
        } else {
            root = current;
        }
    }

    free(path);
    return root;
}

// Function to print the tree in-order
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Main function to test the AVL tree
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

    return 0;
}
