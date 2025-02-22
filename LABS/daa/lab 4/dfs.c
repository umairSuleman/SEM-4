#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to perform DFS traversal
void DFS(struct Graph* graph, int vertex) {
    struct Node* adjList = graph->adjLists[vertex];
    struct Node* temp = adjList;

    // Mark the current node as visited and print it
    graph->visited[vertex] = 1;
    printf("Push order: %d\n", vertex);

    // Recur for all the vertices adjacent to this vertex
    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }

        temp = temp->next;
    }

    printf("Pop order: %d\n", vertex);
}

// Function to perform DFS for all vertices (handles disconnected graphs)
void DFSDisconnected(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->visited[i] == 0) {
            DFS(graph, i);
        }
    }
}

int main() {
    struct Graph* graph = createGraph(7); // Example with 7 vertices

    // Adding edges to create a disconnected graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 4, 5); // Disconnected component

    printf("DFS Traversal for Disconnected Graph:\n");
    DFSDisconnected(graph);

    return 0;
}
