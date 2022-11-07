#include <stdio.h>
#include "stack.c"
#include "queue.c"

Stack *RemoveKey(Stack *S, char c)
{
    Stack *S2 = createStack(S->capacity); // xwrhs capacity to declaration
    while (!isEmptyS(S))
    {
        char tmp = pop(S);
        if (tmp != c)
        {
            push(S2, tmp);
        }
    }
    return S2;
}

void RemoveKey2(Stack *S, char c)
{
    if (isEmptyS(S))
    {
        return;
    }
    char tmp = pop(S);
    RemoveKey2(S, c);
    if (tmp != c)
    {
        push(S, tmp);
    }
}

void print_S(Stack *S)
{
    while (S->top != -1)
    {
        printf("%c ,", pop(S));
    }
}
int main()
{
    Stack *s = createStack(100);
    Stack *new;

    push(s, 'a');
    push(s, 'b');
    push(s, 'a');
    push(s, 'a');
    push(s, 'k');
    push(s, 'm');
    push(s, 'p');
    push(s, 'k');

    RemoveKey2(s, 'k');
    print_S(s);
    return 0;
}