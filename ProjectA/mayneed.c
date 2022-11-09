

int I_Insert(Info **head_ref, Info *newInfo)
{
    Info *curr;
    /*IF EMPTY*/
    if (isInfoEmpty(*head_ref) || isInfoEmpty(newInfo))
        return 1;
    curr = *head_ref;
    /*CHECK IF ITS THE FIRST ELEMENT*/
    if (newInfo->itm < curr->itm)
    {
        newInfo->inext = curr;
        curr->iprev = newInfo;
        newInfo->iprev = NULL;
        *head_ref = newInfo;
        return 0;
    }
    while (curr->inext != NULL && curr->inext->itm < newInfo->itm)
    {
        curr = curr->inext;
    }
    /*an den einai to teleuteo kai to itm yparxei hdh*/
    if (curr->inext != NULL && curr->inext->itm == newInfo->itm)
        return 1;
    newInfo->inext = curr->inext;
    newInfo->iprev = curr;
    curr->inext = newInfo;
    if (newInfo->inext != NULL)
        newInfo->inext->iprev = newInfo;

    return 0;
}
