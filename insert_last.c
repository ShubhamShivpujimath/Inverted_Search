#include "inverted_Search.h"

extern char *filename;

int insert_at_last(Wlist **head, data_t *data)
{
    // 1. create a node
    Wlist *new = malloc(sizeof(Wlist));
    if (new == NULL)
    {
        return FAILURE;
    }

    // update data and link field
    new->file_count = 1;
    strncpy(new->word, data, WORD_SIZE - 1);
    new->word[WORD_SIZE - 1] = '\0';
    new->Tlink = NULL;
    new->link = NULL;

    if (update_link_table(&new) != SUCCESS)
    {
        free(new);   // don't leave a half-built node in the list
        return FAILURE;
    }

    // head is empty or not
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    // if non empty -- traverse to the last node
    Wlist *temp = *head;
    while (temp->link)
    {
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}

int update_link_table(Wlist **head)
{
    // create a node
    Ltable *new = malloc(sizeof(Ltable));
    if (new == NULL)
    {
        return FAILURE;
    }
    new->word_count = 1;
    strncpy(new->file_name, filename, FNAME_SIZE - 1);
    new->file_name[FNAME_SIZE - 1] = '\0';
    new->table_link = NULL;

    // establish the connection between Wlist and Tlink
    (*head)->Tlink = new;
    return SUCCESS;
}