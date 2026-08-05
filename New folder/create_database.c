#include "inverted_Search.h"

char *filename;

int create_database(Flist *f_head, Wlist *head[])
{
    if (f_head == NULL)
    {
        printf("File list is empty. Nothing to create.\n");
        return FAILURE;
    }

    while (f_head)
    {
        // read each file one after the other
        read_datafile(f_head, head, f_head->file_name);
        // move the file head to next node
        f_head = f_head->link;
    }
    return SUCCESS;
}

// function to read the content of the file and add words to the database
Wlist *read_datafile(Flist *f_head, Wlist *head[], char *file_name)
{
    // open the file in read mode
    FILE *fptr = fopen(file_name, "r");
    char word[WORD_SIZE];
    filename = file_name;

    if (fptr == NULL)
    {
        printf("Error: could not open file %s\n", file_name);
        return NULL;
    }

    // reading each word till EOF
    while (fscanf(fptr, "%s", word) != EOF)
    {
        int flag = 1;   // reset for every single word

        // find the bucket index of the word
        int index = hash_function(word);

        if (head[index] != NULL)
        {
            Wlist *temp = head[index];
            // traverse and check for a repeated word
            while (temp)
            {
                if (!strcmp(temp->word, word))
                {
                    update_word_count(&temp, file_name);
                    flag = 0;
                    break;
                }
                temp = temp->link;   // advance -- was missing originally
            }
        }

        // if not a duplicate word
        if (flag == 1)
        {
            insert_at_last(&head[index], word);
        }
    }

    fclose(fptr);
    return head[0];
}

int update_word_count(Wlist **head, char *filename)
{
    Wlist *node = *head;

    // case 1: word has no file entries yet (defensive -- normally insert_at_last
    // already creates the first Ltable entry, but this keeps the function safe
    // to call from anywhere)
    if (node->Tlink == NULL)
    {
        Ltable *new_entry = (Ltable *)malloc(sizeof(Ltable));
        if (new_entry == NULL)
        {
            return FAILURE;
        }
        strncpy(new_entry->file_name, filename, FNAME_SIZE - 1);
        new_entry->file_name[FNAME_SIZE - 1] = '\0';
        new_entry->word_count = 1;
        new_entry->table_link = NULL;

        node->Tlink = new_entry;
        node->file_count = 1;
        return SUCCESS;
    }

    // case 2: search existing file list for this filename
    Ltable *temp = node->Tlink;
    Ltable *prev = NULL;
    while (temp)
    {
        if (!strcmp(temp->file_name, filename))
        {
            temp->word_count++;   // same file -> bump word count
            return SUCCESS;
        }
        prev = temp;
        temp = temp->table_link;
    }

    // case 3: new file, word already seen elsewhere -> add new file node
    Ltable *new_entry = (Ltable *)malloc(sizeof(Ltable));
    if (new_entry == NULL)
    {
        return FAILURE;
    }
    strncpy(new_entry->file_name, filename, FNAME_SIZE - 1);
    new_entry->file_name[FNAME_SIZE - 1] = '\0';
    new_entry->word_count = 1;
    new_entry->table_link = NULL;

    prev->table_link = new_entry;
    node->file_count++;   // new file -> bump file count

    return SUCCESS;
}