#include "inverted_Search.h"

int search(Wlist *head, char *word)
{
    // check if the list is empty or not
    if (head == NULL)
    {
        printf("List is empty\n");
        return FAILURE;
    }

    while (head)
    {
        // compare the node word with the input word
        if (!(strcmp(head->word, word)))
        {
            printf("\nWord \"%s\" is present in %d file(s)\n", head->word, head->file_count);

            printf("  %-25s %s\n", "File Name", "Word Count");
            printf("  %-25s %s\n", "-------------------------", "-----------");

            Ltable *Thead = head->Tlink;
            while (Thead)
            {
                printf("  %-25s %d\n", Thead->file_name, Thead->word_count);
                Thead = Thead->table_link;
            }
            printf("\n");
            return SUCCESS;
        }
        head = head->link;
    }

    printf("Search word \"%s\" is not found\n", word);
    return FAILURE;
}