#include "inverted_Search.h"

// single source of truth for bucket index -- used everywhere instead of
// recomputing tolower(word[0]) % 97 in multiple places (which had drifted
// out of sync in the original code)
int hash_function(const char *word)
{
    int index = tolower(word[0]) % 97;
    if (!(index >= 0 && index <= 25))
    {
        // numbers and symbols all land in the last bucket
        index = 26;
    }
    return index;
}

// simple existence check (declared in header, not previously implemented)
int isfileexist(char *filename)
{
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        return FILE_NOTAVAILABLE;
    }
    fclose(fptr);
    return SUCCESS;
}