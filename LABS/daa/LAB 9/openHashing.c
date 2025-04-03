#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 13               //can be given as user input too

typedef struct node{
    char * value;
    struct node *next;
}node;

typedef struct hash{
    node * table[TABLE_SIZE];
}hash;

node * createNode(char * key){
    node* newNode= (node *)malloc(sizeof(node));

    newNode->value=strdup(key);
    newNode->next=NULL;

    return newNode;
}

void initHashTable(hash * ht){
    for(int i=0; i<TABLE_SIZE; i++){
        ht->table[i]=NULL;              //initialised to NULL meaning no value being stored
    }
}

int hashFunction(hash * ht, char * key){
    int sum=0;
    for(int i=0; key[i] != '\0'; i++){
        char c=toupper(key[i]);         //converts to upper just in case

        if(isalpha(c)){
            sum+=(c-'A' +1);            //gets characters postiion and adds to sum
        }
    }
    return sum % TABLE_SIZE;            //hash function
}

void insert(hash * ht, char * key){
    int index=hashFunction(ht, key);
    node * newNode=createNode(key);

    if(ht->table[index]==NULL){
        ht->table[index]=newNode;     //inserting first value;
    }
    else{
        node * temp=ht->table[index];
        while(temp->next !=NULL){
            temp=temp->next;        //temp goes to last node
        }
        temp->next=newNode;
    }
}

int search(hash * ht, char * key){

    int index=hashFunction(ht, key);

    if(ht->table[index]==NULL){
        return 0;
    }

    node* curr = ht->table[index];
    while(curr!=NULL){
        if(strcmp(curr->value, key)==0){
            return 1;       //value found
        }
        curr=curr->next;

    }

    return 0;               //value not found
}

void freeHashTable(hash *ht) {
    for(int i=0; i<TABLE_SIZE; i++) {
        node* curr = ht->table[i];
        while(curr != NULL) {
            node* temp = curr;
            curr = curr->next;
            free(temp->value);
            free(temp);
        }
    }
}


void printHashTable(hash *ht) {
    node *curr;

    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d] ", i);
        
        if(ht->table[i] != NULL) {                      //check if value is null before printing
            printf("->%s", ht->table[i]->value);
            curr = ht->table[i]->next;
            
            while(curr != NULL) {
                printf("->%s", curr->value);
                curr = curr->next;
            }
        }
        printf("->NULL\n");
    }
}

int main(){

    hash ht;
    initHashTable(&ht);

    int n;
    printf("Enter number of keys:");
    scanf("%d", &n);

    char * keys[n];

    printf("Enter the key value:\n");
    for(int i=0; i<n; i++){
        keys[i]=(char*)malloc(sizeof(char));
        scanf("%s", keys[i]);
    }

    for(int i=0; i<n; i++){
        insert(&ht, keys[i]);
    }

    printf("Hash Table: \n");
    printHashTable(&ht);

    char key[50];

    printf("Enter value to be searched:");
    scanf("%s", key);

    if(search(&ht, key)){
        printf("Value found.\n");
    }else{
        printf("Value not found.\n");
    }

    for(int i=0; i<n; i++) {
        free(keys[i]);
    }
    freeHashTable(&ht);

    return 0;
}
