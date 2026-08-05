#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>

//defining macros
#define FAILURE   -1
#define SUCCESS    0
#define FNAME_SIZE 256
#define WORD_SIZE  30
#define FILE_EMPTY -2
#define FILE_NOTAVAILABLE -3
#define REPEATATION -4

// ---- ANSI color codes for decorated terminal output ----
#define COLOR_RESET    "\033[0m"
#define COLOR_BOLD     "\033[1m"
#define COLOR_RED      "\033[31m"
#define COLOR_GREEN    "\033[32m"
#define COLOR_YELLOW   "\033[33m"
#define COLOR_BLUE     "\033[34m"
#define COLOR_MAGENTA  "\033[35m"
#define COLOR_CYAN     "\033[36m"

//Structure for file list
typedef char data_t;
typedef struct file_node
{
	data_t file_name[FNAME_SIZE];
	struct file_node *link;

}Flist;

//Structure for link table
typedef struct linkTable_node
{
	int word_count;
	data_t file_name[FNAME_SIZE];
	struct linkTable_node *table_link;
}Ltable;

//structure to store word count
typedef struct word_node
{
	int file_count;
	data_t word[WORD_SIZE];
	Ltable *Tlink;
	struct word_node *link;

}Wlist;

// create file linked list (with duplicate check)
int to_create_list_of_files(Flist **f_head, char *name);

// build the full database from the file linked list
int create_database(Flist *f_head, Wlist *head[]);

// read contents of a file and add its words into the database
Wlist * read_datafile(Flist *file, Wlist *head[], char *filename);

// create word_list node
int insert_at_last(Wlist **head, data_t *data);

// create/attach a new Ltable node to a Wlist node
int update_link_table(Wlist **head);

// update word count / file count when a word is seen again
int update_word_count(Wlist **head, char *file_name);

// print_word_count -- traverse a bucket's list and print it
int print_word_count(Wlist *head);

// searching a word
int search(Wlist *head, char *word);

// display the full database
void display_database(Wlist *head[]);

// save the database to a file
int save_database(Wlist *head[]);

// write one bucket's list into the save file
void write_databasefile(Wlist *head, FILE *databasefile);

// update the database with a new file
int update_database(Wlist *head[], Flist **f_head);

// check whether a file exists / is empty
int isFileEmpty(char *filename);

// validate CLA files and build the file linked list
int file_validation_n_file_list(Flist **f_head, char *argv[]);

// single source of truth for bucket index calculation
int hash_function(const char *word);

// check plain existence of a file
int isfileexist(char *filename);

#endif