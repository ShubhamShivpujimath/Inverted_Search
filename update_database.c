#include "inverted_Search.h"

int update_database(Wlist *head[], Flist **f_head)
{
    char file_name[FNAME_SIZE];   // was wrongly declared as char *file_name[FNAME_SIZE]

    printf("Enter the filename to update the database: ");
    scanf("%s", file_name);

    // validation of the given file -- available, has content
    int empty = isFileEmpty(file_name);
    if (empty == FILE_NOTAVAILABLE)
    {
        printf("File %s is not available\n", file_name);
        printf("Hence not added to the database\n");
        return FAILURE;
    }
    else if (empty == FILE_EMPTY)
    {
        printf("File %s is empty or has no content\n", file_name);
        printf("Hence not added to the database\n");
        return FAILURE;
    }

    // check for duplicate / insert into the file linked list
    int ret_val = to_create_list_of_files(f_head, file_name);
    if (ret_val == REPEATATION)
    {
        printf("File %s is already present in the database\n", file_name);
        return FAILURE;
    }
    else if (ret_val != SUCCESS)
    {
        printf("Unexpected error while adding %s\n", file_name);
        return FAILURE;
    }

    printf("Successfully inserted %s into file linked list\n", file_name);

    // update just this one new file's words into the existing database
    // (NOT create_database, which would re-walk and re-process the whole list)
    read_datafile(NULL, head, file_name);

    return SUCCESS;
}