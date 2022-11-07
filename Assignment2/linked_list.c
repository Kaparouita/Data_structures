#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node
{
    int data;
    struct Node *next;
};

void printList(Node *n)
{
    while (n != NULL)
    {
        printf(" %d ", n->data);
        n = n->next;
    }
}

/* Given a reference (pointer to pointer) to the head of a list
and an int, inserts a new node on the front of the list. */
void push(Node **head_ref, int new_data)
{
    /* 1. allocate node */
    Node *new_node = (Node *)malloc(sizeof(Node));

    /* 2. put in the data */
    new_node->data = new_data;

    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);

    /* 4. move the head to point to the new node */
    (*head_ref) = new_node;
}
