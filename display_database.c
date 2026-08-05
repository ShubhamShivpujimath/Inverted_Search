#include "inverted_Search.h"

void display_database(Wlist *head[])
{
    printf("\n");
    printf("╔════════╦═══════════════════╦═════════════╦═════════════════════════════════════╗\n");
    printf("║ %-6s ║ %-17s ║ %-11s ║ %-35s ║\n", "Index", "Word", "File Count", "File Name : Word Count");
    printf("╠════════╬═══════════════════╬═════════════╬═════════════════════════════════════╣\n");

    int any = 0;
    for (int i = 0; i < 27; i++)
    {
        if (head[i] != NULL)
        {
            any = 1;
            print_word_count(head[i]);
        }
    }

    if (!any)
    {
        printf("║ %-78s ║\n", "Database is empty -- run 'Create Database' first");
    }

    printf("╚════════╩═══════════════════╩═════════════╩═════════════════════════════════════╝\n\n");
}

// print the word count for one bucket's linked list
int print_word_count(Wlist *head)
{
    while (head != NULL)
    {
        int index = hash_function(head->word);   // single source of truth

        Ltable *Thead = head->Tlink;

        // build the "filename : count" string for the first file so it
        // fits on the same row as the word / index / file_count
        char first_col[FNAME_SIZE + 20];
        first_col[0] = '\0';
        if (Thead != NULL)
        {
            snprintf(first_col, sizeof(first_col), "%s : %d", Thead->file_name, Thead->word_count);
        }

        printf("║ %-6d ║ %-17s ║ %-11d ║ %-35s ║\n",
               index, head->word, head->file_count, first_col);

        if (Thead != NULL)
        {
            Thead = Thead->table_link;
        }

        // any additional files this word appears in get their own row,
        // with the first three columns left blank
        while (Thead != NULL)
        {
            char col[FNAME_SIZE + 20];
            snprintf(col, sizeof(col), "%s : %d", Thead->file_name, Thead->word_count);
            printf("║ %-6s ║ %-17s ║ %-11s ║ %-35s ║\n", "", "", "", col);
            Thead = Thead->table_link;
        }

        printf("╟────────╫───────────────────╫─────────────╫─────────────────────────────────────╢\n");

        head = head->link;
    }
    return SUCCESS;
}