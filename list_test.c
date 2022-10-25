#include <stdio.h>

struct flight
{
    int id;
    struct flight *next;
    struct flight *prev;
};

struct node_S
{
    struct flight *head;
    unsigned int length;
};

typedef struct flight *flight;
typedef struct node_S *node; // Define node as pointer of data type struct LinkedList

node createNode()
{
    node temp = (node)malloc(sizeof(node *)); // allocate memory using malloc()
    temp->head = NULL;
    temp->length = 0;
    return temp; // return the new node
}

int node_put(node node, int *id)
{
    struct flight *newflight;
    /*
     if (SymTable_contains(node, id) == 1)  using my contain to check
          return 0;
    */

    newflight = (struct flight *)malloc(sizeof(struct flight));

    newflight->id = id;
    newflight->next = node->head;
    newflight->prev = NULL;
    if (node->head != NULL)
        node->head->prev = newflight;
    node->head = newflight;
    node->length++;
    return 1;
}

void print_table(node node)
{
    struct flight *print;
    int i = 0;
    print = node->head;
    printf("START PRINTING\n  INDEX\tID\tYEAR\n");
    while (print != NULL)
    {

        printf(" %i\t%d\t\n", i, print->id);
        print = print->next;
        i++;
    }
    printf("END PRINTING\n/----------------------------------------/\n");
    return;
}

/*b i)*/
/*den xreiazonte ta head afou sthn askhsh pernw to prwto*/
node SetMinus(node a, node b)
{
    node c = createNode();
    int num_a, num_b;
    /*vres to teuletaio ths b*/
    while (b->head->next != NULL)
    {
        b->head = b->head->next;
    }
    while (a->head != NULL)
    {
        num_a = a->head->id;
        num_b = b->head->id;
        /* an einai mikrotero tote den yparxei sthn b, an h b exei teliwsei tote pali den yparxei sthn b to stoixeio*/
        if (num_a < num_b || b->head->prev == NULL)
        {
            node_put(c, num_a);
            a->head = a->head->next;
        }
        /*an to a einai megalytero b++*/
        else if (num_a > num_b)
        {
            b->head = b->head->prev;
        }
        /*an einai isa kai ta dyo ++*/
        else if (num_a == num_b)
        {
            a->head = a->head->next;
            b->head = b->head->prev;
        }
    }
    return c;
}

void SetMinus2(flight a, flight b, node c)
{
    int arr[100] = {0};
    printf("\n : %d", b->id);

    if (a->next == NULL)
        return;
    else if (b->next == NULL)
    {
        int i = 0, j = 0;
        while (i < 6)
        {

            if (arr[j] != 0)
            {
                printf("\n : %d", arr[j]);
                i++;
            }

            j++;
        }
        return;
        node_put(c, a->id);
        SetMinus2(a->next, b, c);
    }
    else if (b->id < a->id)
    {
        printf("\n : %d", b->id);
        SetMinus2(a, b->next, c);
    }
    else if (b->id == a->id)
    {
        SetMinus2(a->next, b, c);
    }
    else
    {
        arr[b->id] = b->id;
        SetMinus2(a, b->next, c);
    }
    return;
}

int main()
{
    node a = createNode();
    node b = createNode();
    node c = createNode();

    node_put(a, 42);
    node_put(a, 40);
    node_put(a, 36);
    node_put(a, 25);
    node_put(a, 20);
    node_put(a, 15);
    node_put(a, 11);
    node_put(a, 9);
    node_put(a, 7);
    node_put(a, 5);
    node_put(a, 3);
    node_put(a, 1);

    node_put(b, 3);
    node_put(b, 9);
    node_put(b, 11);
    node_put(b, 12);
    node_put(b, 15);
    node_put(b, 20);
    node_put(b, 36);

    SetMinus2(a->head, b->head, c);

    // print_table(c);
    return 0;
}