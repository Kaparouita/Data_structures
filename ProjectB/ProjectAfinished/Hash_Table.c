
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pss.h"

static unsigned int SymTable_hash(int subinfo_ID, SymTable_S *table)
{
    return (subinfo_ID * table->hs) % table->buckets;
}

SymTable_S *SymTable_new(int BUCKETS, unsigned hs)
{

    SymTable_S *new_Symtable = malloc(sizeof(SymTable_S *));
    new_Symtable->Subs = malloc(BUCKETS * sizeof(struct SubInfo *));
    new_Symtable->length = 0;
    new_Symtable->buckets = BUCKETS;
    new_Symtable->hs = hs;
    return new_Symtable;
}

int SymTable_contains(SymTable_S *table, SubInfo *sub)
{
    SubInfo *curr;
    int index;
    assert(table);
    assert(sub);
    index = SymTable_hash(sub->sId, table); /*get the key*/
    if (table->Subs[index] != NULL)
    {
        curr = table->Subs[index];
        /*tsekare thn alysida tou*/
        while (curr != NULL)
        {
            if (curr->sId == sub->sId) /*if its the same return 1*/
                return 1;
            curr = curr->snext;
        }
    }
    return 0;
}

int SymTable_insert(SymTable_S *table, SubInfo *subinfo)
{

    struct binding *new_obj;
    int index, i;
    assert(table);
    assert(subinfo);
    if (SymTable_contains(table, subinfo) == 1) /*an yparxei return 1*/
        return 1;
    index = SymTable_hash(subinfo->sId, table);
    /*if index position is already taken*/
    if (table->Subs[index] != NULL)
    {
        if (Sub_Insert(&(table->Subs[index]), subinfo))
            return 1;
    }
    else
        table->Subs[index] = subinfo;
    table->length++;
    return 0;
}

int SymTable_remove(SymTable_S *table, SubInfo *sub)
{
    int index;
    assert(table);
    assert(sub);
    index = SymTable_hash(sub->sId, table);
    if (table->Subs[index] != NULL)
        if (SL_delete(&table->Subs[index], sub))
            return 1;
    table->length--;
    return 0;
}

SubInfo *SymTable_get(SymTable_S *table, int sId)
{
    SubInfo *curr;
    int index;
    assert(table);
    index = SymTable_hash(sId, table);
    if (table->Subs[index] != NULL)
    {
        curr = table->Subs[index];
        /*tsekare thn alysida tou*/
        while (curr != NULL)
        {
            if (curr->sId == sId) /*if its the same return 1*/
                return curr;
            curr = curr->snext;
        }
    }
    return NULL;
}

void print_table(SymTable_S *oSymTable)
{
    int i = 0;
    printf("START PRINTING\n");
    assert(oSymTable);

    for (i = 0; i < oSymTable->buckets; i++)
    {
        if (oSymTable->Subs[i] != NULL)
        {
            printf("TABLE INDEX : %d", i);
            printAllSubs(oSymTable);
        }
    }
    printf("END PRINTING\n/----------------------------------------/\n");
    return;
}

/*
int main()
{
    int a[6] = {31, 5, 6, 45, 1, -1};
    int b[6] = {57, 35, 6, 43, 1, -1};
    int c[6] = {63, 35, 6, 43, 1, -1};

    SubInfo *sub = SubInfoConstractor(4, 2000, a, 6);
    SubInfo *sub3 = SubInfoConstractor(10, 1999, c, 6);
    SubInfo *sub1 = SubInfoConstractor(5, 4000, b, 6);
    SubInfo *sub2 = SubInfoConstractor(6, 2365, c, 6);

    SymTable_S *table = SymTable_new(5, 65599);
    SymTable_insert(table, sub);
    SymTable_insert(table, sub1);
    SymTable_insert(table, sub2);
    SymTable_insert(table, sub3);

    print_table(table);
}*/
