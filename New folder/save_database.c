#include "inverted_Search.h"

int save_database(Wlist *head[])
{
    char file_name[FNAME_SIZE];

    printf("Enter the filename: ");   // was "pritf" typo
    scanf("%s", file_name);

    // open the file
    FILE *fptr = fopen(file_name, "w");
    if (fptr == NULL)
    {
        printf("Error: could not create/open file %s\n", file_name);
        return FAILURE;
    }

    // array of heads
    for (int i = 0; i < 27; i++)
    {
        // check if the list is empty or not
        if (head[i] != NULL)
        {
            write_databasefile(head[i], fptr);
        }
    }

    fclose(fptr);   // was missing
    printf("Database saved to %s\n", file_name);
    return SUCCESS;
}

void write_databasefile(Wlist *head, FILE *datafile)
{
    /*
    #[0] : [word] : [file_count] : filename : [word count]
                                    filename : [word count]

    #[1] : [word] : [file_count] : filename : [word count]
                                    filename : [word count]
    */
    while (head != NULL)
    {
        int index = hash_function(head->word);

        fprintf(datafile, "#[%d] : [%s] : [%d] : ", index, head->word, head->file_count);

        Ltable *Thead = head->Tlink;
        int first = 1;
        while (Thead != NULL)
        {
            if (first)
            {
                fprintf(datafile, "%s : [%d]\n", Thead->file_name, Thead->word_count);
                first = 0;
            }
            else
            {
                // indent so it lines up under the first filename column
                fprintf(datafile, "\t\t\t\t\t  %s : [%d]\n", Thead->file_name, Thead->word_count);
            }
            Thead = Thead->table_link;
        }

        head = head->link;
    }
}