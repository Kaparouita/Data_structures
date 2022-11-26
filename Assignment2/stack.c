// C program for array implementation of stack
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack Stack;
// A structure to represent a stack
struct Stack
{
    int top;
    unsigned capacity;
    int *array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
Stack *createStack(unsigned capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack is full when top is equal to the last index
int isFullS(Stack *stack)
{
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int isEmptyS(Stack *stack)
{
    return stack->top == -1;
}

// Function to add an item to stack. It increases top by 1
void push(Stack *stack, int item)
{
    if (isFullS(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack. It decreases top by 1
int pop(Stack *stack)
{
    if (isEmptyS(stack))
        return '0';
    return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
int peek(Stack *stack)
{
    if (isEmptyS(stack))
        return '0';
    return stack->array[stack->top];
}

