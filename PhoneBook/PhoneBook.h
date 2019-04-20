#ifndef PhoneBook_H
#define PhoneBook_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PhoneBookStruct.h"
#include "PhoneBookUI.h"

#define MAX_LENGTH 2000
#define strtokNext strtok(NULL, ",")
#define FALSE 0
#define TRUE 1


typedef struct contact Contact;
typedef Contact* Contact_ptr;

typedef struct bTreeNode BTreeNode;
typedef BTreeNode* BTreeNode_ptr;

// parse user input
int parser(BTreeNode_ptr root);
// parse option -r
int parseRetrieve(BTreeNode_ptr root, char* keyword);
// parser after retrieving
int parserForEditDelete(BTreeNode_ptr root, int lineN);
// parse option -e
int parseEdit(BTreeNode_ptr* root, char* keyword);
// parse option -d
int parseDelete(BTreeNode_ptr root, char* keyword);
// parse option -s
int showAllList(BTreeNode_ptr root);
// parse option -a
int parseAdd(BTreeNode_ptr root, char* input);

// tokenize contact data
Contact_ptr strtokContact(char* input);
// load contacts from a file
int loadContact(BTreeNode_ptr* root, char* filename);
// save contacts to a file
int saveToFile(BTreeNode_ptr root, char* filename);
// reflect any change before quitting the program, 
void exitProgram(BTreeNode_ptr root, int ifchanged);

// make name to upper case
void toUpperCase(char* input);
#endif