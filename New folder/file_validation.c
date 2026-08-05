#include "inverted_Search.h"

int file_validation_n_file_list(Flist **f_head, char *argv[])
{
    int i = 1, empty; // output file is exempted / argv[0] is the program name

    while (argv[i] != NULL)
    {
        empty = isFileEmpty(argv[i]);

        if (empty == FILE_NOTAVAILABLE)
        {
            printf("File %s is not available\n", argv[i]);
            printf("Hence we are not adding that file to database\n");
            i++;
            continue;
        }
        else if (empty == FILE_EMPTY)
        {
            printf("File %s is empty or not having any content\n", argv[i]);
            printf("Hence we are not adding that file to database\n");
            i++;
            continue;
        }
        else
        {
            int ret_val = to_create_list_of_files(f_head, argv[i]);
            if (ret_val == SUCCESS)
            {
                printf("Successfully inserted %s file into file linked list\n", argv[i]);
            }
            else if (ret_val == REPEATATION)
            {
                printf("File %s already present in the linked list so not added again\n", argv[i]);
            }
            else
            {
                printf("Unexpected error while adding %s\n", argv[i]);
            }
            i++;   // was missing -- caused an infinite loop on the success path
        }
    }
    return SUCCESS;
}

// function to check file availability and file contents
int isFileEmpty(char *filename)
{
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        // covers ENOENT and any other reason fopen failed (permissions, etc.)
        return FILE_NOTAVAILABLE;
    }

    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    fclose(fptr);   // was leaking the file handle

    if (size == 0)
    {
        return FILE_EMPTY;
    }

    return SUCCESS;   // file exists and has content
}

// function to create file linked list (insert at last, with duplicate check)
int to_create_list_of_files(Flist **f_head, char *name)
{
    // check for duplicate first
    Flist *temp = *f_head;
    while (temp != NULL)
    {
        if (!strcmp(temp->file_name, name))
        {
            return REPEATATION;
        }
        temp = temp->link;
    }

    // not a duplicate -- create new node
    Flist *new_node = (Flist *)malloc(sizeof(Flist));
    if (new_node == NULL)
    {
        return FAILURE;
    }
    strncpy(new_node->file_name, name, FNAME_SIZE - 1);
    new_node->file_name[FNAME_SIZE - 1] = '\0';
    new_node->link = NULL;

    // insert at end of list
    if (*f_head == NULL)
    {
        *f_head = new_node;
    }
    else
    {
        Flist *last = *f_head;
        while (last->link != NULL)
        {
            last = last->link;
        }
        last->link = new_node;
    }

    return SUCCESS;
}