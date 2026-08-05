/*********************************************************************
 * NAME: SHUBHAM SHIVPUJIMATH
 * DATE: 07-07-2026
 * DESCRIPTION: INVERTED SEARCH
 **********************************************************************/
#include "inverted_Search.h"

static void print_menu(void)
{
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║        INVERTED SEARCH DATABASE       ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║  1. Create Database                   ║\n");
    printf("║  2. Display Database                  ║\n");
    printf("║  3. Search Database                   ║\n");
    printf("║  4. Update Database                   ║\n");
    printf("║  5. Save Database                     ║\n");
    printf("║  6. Exit                              ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    printf("Enter a Choice: ");
}

int main(int argc, char *argv[])
{
    system("clear");

    if (argc < 2)
    {
        printf("Enter the valid number of arguments\n");
        printf("./inverted.exe file1.txt file2.txt file3.txt ...\n");
        return 0;
    }

    // create the file linked list -- collection of files
    Flist *f_head = NULL;
    Wlist *head[27] = {NULL};

    // validation of CLA files
    file_validation_n_file_list(&f_head, argv);
    if (f_head == NULL)
    {
        printf("No files have been added to the file linked list\n");
        printf("Hence the process got terminated\n");
        return 1;
    }

    int choice;
    do
    {
        print_menu();

        if (scanf("%d", &choice) != 1)
        {
            // clear bad input from stdin so we don't loop forever
            while (getchar() != '\n');
            printf("Invalid input, please enter a number.\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                create_database(f_head, head);
                printf("Database created successfully.\n");
                break;

            case 2:
                display_database(head);
                break;

            case 3:
            {
                char word[WORD_SIZE];
                printf("Enter word to search: ");
                scanf("%s", word);
                int index = hash_function(word);
                search(head[index], word);
                break;
            }

            case 4:
                update_database(head, &f_head);
                break;

            case 5:
                save_database(head);
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice, please try again.\n");
                break;
        }

    } while (choice != 6);

    return 0;
}