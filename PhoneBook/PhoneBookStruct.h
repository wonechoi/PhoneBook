#ifndef PhoneBookStruct_H
#define PhoneBookStruct_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


#define FALSE 0
#define TRUE 1

typedef struct contact Contact;
typedef Contact* Contact_ptr;

typedef struct bTreeNode BTreeNode;
typedef BTreeNode* BTreeNode_ptr;


// insert new contact into PhoneBook
BTreeNode_ptr insertPhoneBook(BTreeNode_ptr tree, Contact_ptr contact);

// create a new node
BTreeNode_ptr createNode(void);
// create a new contact
Contact_ptr createContact(char* firstName, char* lastName, char* mobile);
// set contact data delivered as a parameter
int setData(BTreeNode_ptr this, Contact_ptr data);
// set first name
int setFirstName(Contact_ptr this, char* firstName);
// set last name
int setLastName(Contact_ptr this, char* lastName);
// set mobile
int setMobile(Contact_ptr this, char* mobile);
// set a subtree to leftside of a node
void setLNode(BTreeNode_ptr parent, BTreeNode_ptr child);
// set a subtree to rightside of a node
void setRNode(BTreeNode_ptr parent, BTreeNode_ptr child);

// search data with a first name
void searchByFirstName(BTreeNode_ptr tree, char* firstName, char* result);
void lookForSameFirstName(BTreeNode_ptr node, char* firstName, char* result);

// print Contact
void getContact(BTreeNode_ptr node, char* str);
// get first name of a contact
char* getFirstName(Contact_ptr contact);
// get last name of a contact
char* getLastName(Contact_ptr contact);
// get mobile of a contact
char* getMobile(Contact_ptr contact);

// return an address of left node of a node
BTreeNode_ptr getLNode(BTreeNode_ptr node);
// return an address of right node of a node
BTreeNode_ptr getRNode(BTreeNode_ptr node);

// An imbalance is occuered by LL node (when new node is added to a left of a left of a node)
BTreeNode_ptr rotate_right(BTreeNode_ptr node);
// An imbalance is occuered by RR node (when new node is added to a right of a right of a node)
BTreeNode_ptr rotate_left(BTreeNode_ptr node);
// An imbalance is occuered by LR node (when new node is added to a right of a left of a node)
BTreeNode_ptr rotate_left_right(BTreeNode_ptr node);
// An imbalance is occuered by RL node (when new node is added to a left of a right of a node)
BTreeNode_ptr rotate_right_left(BTreeNode_ptr node);

// check if there is difference over 2 between left height and right heignt
// if then, rebalance the tree
BTreeNode_ptr rebalance(BTreeNode_ptr node);
// return height of a tree
int getHeight(BTreeNode_ptr node);
// return the difference of heights between two sub trees
int calHDiff(BTreeNode_ptr node);

// show every data in the phone book
void listAllData(BTreeNode_ptr node, char* result);
// show every data in the file
void listAllDataToFile(BTreeNode_ptr node, FILE* fp);

// remove node
BTreeNode_ptr removeContact(BTreeNode_ptr tree, char* firstName, char*lastName, int* successed);
void freeNode(BTreeNode_ptr tree);
char* toUpperStr(char* str);

#endif 
