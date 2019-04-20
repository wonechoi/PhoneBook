#include "PhoneBookStruct.h"

struct contact {
	char* firstName;
	char* lastName;
	char* mobile;
};

struct bTreeNode {
	Contact_ptr data;
	BTreeNode_ptr left;
	BTreeNode_ptr right;
};

BTreeNode_ptr insertPhoneBook(BTreeNode_ptr tree, Contact_ptr contact) {

	// if no node, insert a new node
	if (!tree) {
		tree = createNode();
		setData(tree, contact);
	}
	// if the new firstname is smaller than a firstname of current node 
	else if (strcmp(contact->firstName, getFirstName(tree->data)) < 0) {
		tree->left = insertPhoneBook(tree->left, contact);
		tree = rebalance(tree);
	}
	// if the new firstname is bigger than a firstname of current node 
	else if (strcmp(contact->firstName, getFirstName(tree->data)) > 0) {
		tree->right = insertPhoneBook(tree->right, contact);
		tree = rebalance(tree);
	}
	else {
		// if the new lastname is smaller than a lastname of current node 
		if (strcmp(contact->lastName, getLastName(tree->data)) < 0) {
			tree->left = insertPhoneBook(tree->left, contact);
			tree = rebalance(tree);
		}
		// if the new lastname is bigger than a lastname of current node 
		else if (strcmp(contact->lastName, getLastName(tree->data)) >= 0) {
			tree->right = insertPhoneBook(tree->right, contact);
			tree = rebalance(tree);
		}
	}
	return tree;
}

BTreeNode_ptr createNode() {
	BTreeNode_ptr node = (BTreeNode_ptr)malloc(sizeof(BTreeNode));

	if (!node) {
		return NULL;
	}

	node->data = NULL;
	node->left = NULL;
	node->right = NULL;

	return node;
}
Contact_ptr createContact(char* firstName, char* lastName, char* mobile) {
	Contact_ptr contact = (Contact_ptr)malloc(sizeof(Contact));
	if (!contact) {
		return NULL;
	}

	// if each item doesn't have data
	if (!firstName || !lastName || !mobile
		|| strlen(firstName) < 1 || strlen(lastName) < 1 || strlen(mobile) < 1) {
		return NULL;
	}

	if (setFirstName(contact, toUpperStr(firstName)) == 0 ||
		setLastName(contact, toUpperStr(lastName)) == 0 ||
		setMobile(contact, mobile) == 0) {
		return NULL;
	}

	return contact;
}

int setData(BTreeNode_ptr this, Contact_ptr contact) {

	this->data = contact;
	return TRUE;
}
int setFirstName(Contact_ptr this, char* firstName) {
	this->firstName = malloc(strlen(firstName) + 1);
	if (!(this->firstName)) {
		return FALSE;
	}

	strcpy(this->firstName, firstName);
}
int setLastName(Contact_ptr this, char* lastName) {
	this->lastName = malloc(strlen(lastName) + 1);
	if (!(this->lastName)) {
		return FALSE;
	}

	strcpy(this->lastName, lastName);
}
int setMobile(Contact_ptr this, char* mobile) {
	this->mobile = malloc(strlen(mobile) + 1);
	if (!(this->mobile)) {
		return FALSE;
	}

	strcpy(this->mobile, mobile);
}
void setLNode(BTreeNode_ptr parent, BTreeNode_ptr child) {
	parent->left = child;
}
void setRNode(BTreeNode_ptr parent, BTreeNode_ptr child) {
	parent->right = child;
}

int ifFullNameIsExisted(BTreeNode_ptr node, char* firstName, char* lastName) {
	// current node
	BTreeNode_ptr cNode = node;
	char* cFirstname;
	char* cLastname;

	while (cNode != NULL) {
		cFirstname = getFirstName(cNode->data);
		cLastname = getLastName(cNode->data);

		//look for same name
		if (strcmp(firstName, cFirstname) == 0) {
			if (strcmp(lastName, cLastname) < 0) {
				cNode = getLNode(cNode);
			}
			else if (strcmp(lastName, cLastname) > 0) {
				cNode = getRNode(cNode);
			}
			else {
				return TRUE;
			}
		}
		else if (strcmp(firstName, cFirstname) < 0) {
			cNode = getLNode(cNode);
		}
		else {
			cNode = getRNode(cNode);
		}
	}
	return FALSE;
}

void searchByFirstName(BTreeNode_ptr node, char* firstName, char* result) {

	// current node
	BTreeNode_ptr cNode = node;
	char* cFirstname;

	while (cNode != NULL) {
		cFirstname = getFirstName(cNode->data);

		if (strcmp(firstName, cFirstname) == 0) {
			//look for other contacts which have same first name
			lookForSameFirstName(cNode, firstName, result);
			return;
		}
		else if (strcmp(firstName, cFirstname) < 0) {
			cNode = getLNode(cNode);
		}
		else {
			cNode = getRNode(cNode);
		}
	}
}
void lookForSameFirstName(BTreeNode_ptr node, char* firstName, char* result) {

	if (!node) {
		return;
	}

	BTreeNode_ptr cNode = node;
	char* cFirstname = getFirstName(node->data);

	// same firstname could be in the right part of left child
	// or in the left part of right child
	if (strcmp(firstName, cFirstname) == 0) {
		lookForSameFirstName(node->left, firstName, result);
		getContact(node, result);
		lookForSameFirstName(node->right, firstName, result);
	}
	else if (strcmp(firstName, cFirstname) < 0) {
		lookForSameFirstName(node->left, firstName, result);
	}
	else {
		lookForSameFirstName(node->right, firstName, result);
	}
	
}

void getContact(BTreeNode_ptr node, char* str) {

	char* contact = (char*)malloc(500);
	sprintf(contact, "%s %s: %s\n", node->data->firstName, node->data->lastName, node->data->mobile);
	strcat(str, contact);
	free(contact);
}

char* getFirstName(Contact_ptr contact) {
	return contact->firstName;
}
char* getLastName(Contact_ptr contact) {
	return contact->lastName;
}
char* getMobile(Contact_ptr contact) {
	return contact->mobile;
}

BTreeNode_ptr getLNode(BTreeNode_ptr node) {
	if (!node) {
		return NULL;
	}
	return node->left;
}
BTreeNode_ptr getRNode(BTreeNode_ptr node) {
	if (!node) {
		return NULL;
	}
	return node->right;
}

BTreeNode_ptr rotate_right(BTreeNode_ptr node) {
	BTreeNode_ptr parent = node;
	BTreeNode_ptr child = getLNode(parent);

	// rotate the tree to the right
	parent->left = getRNode(child); // connect a right subnode of child node to under a left subnode of parent
	child->right = parent; // connect parent node to under a right subnode of child node

	return child;
}
BTreeNode_ptr rotate_left_right(BTreeNode_ptr node) {
	BTreeNode_ptr parent = node;
	BTreeNode_ptr child = getLNode(parent);

	parent->left = rotate_left(child); // rotate its child tree to the left
	return rotate_right(parent); // rotate the tree to the right
}
BTreeNode_ptr rotate_left(BTreeNode_ptr node) {
	BTreeNode_ptr parent = node;
	BTreeNode_ptr child = getRNode(parent);

	// rotate the tree to the left
	parent->right = getLNode(child); //connect a left subnode of child node to under a left subnode of parent
	child->left = parent; // connect parent node to under left a subnode of child node

	return child;
}
BTreeNode_ptr rotate_right_left(BTreeNode_ptr node) {
	BTreeNode_ptr parent = node;
	BTreeNode_ptr child = getRNode(parent);

	parent->right = rotate_right(child); // rotate its child tree to the right
	return rotate_left(parent); // rotate the tree to the left
}

BTreeNode_ptr rebalance(BTreeNode_ptr node) {
	int hDiff = calHDiff(node);

	// the difference of heights between the left sub tree and the right sub tree is same with or over than 2

	// if a height of left side is bigger
	if (hDiff >= 2) {
		// if the left sub tree of the child is higher than the right sub tree of the child
		// rotate sub trees right
		if (calHDiff(getLNode(node)) > 0) {
			node = rotate_right(node);
		}
		// if the right sub tree of the child is higher than the left sub tree of the child,
		// just to rotate it right occurs another unbalanced tree
		// therefore, rotate the sub tree left then rotate parent tree right
		else {
			node = rotate_left_right(node);
		}
	}
	// if a height of right side is bigger
	if (hDiff <= -2) {
		if (calHDiff(getRNode(node)) < 0) {
			node = rotate_left(node);
		}
		else {
			node = rotate_right_left(node);
		}
	}

	return node;
}
int getHeight(BTreeNode_ptr node) {
	int leftH, rightH;

	if (!node) {
		return FALSE;
	}

	leftH = getHeight(getLNode(node));
	rightH = getHeight(getRNode(node));

	if (leftH > rightH) {
		return leftH + 1;
	}
	else {
		return rightH + 1;
	}
}
int calHDiff(BTreeNode_ptr node) {
	int leftH, rightH;

	if (!node) {
		return FALSE;
	}

	leftH = getHeight(getLNode(node));
	rightH = getHeight(getRNode(node));

	return leftH - rightH;
}

void listAllData(BTreeNode_ptr node, char* result) {
	if (!node) {
		return;
	}

	listAllData(node->left, result);
	getContact(node, result);
	listAllData(node->right, result);
}

void listAllDataToFile(BTreeNode_ptr node, FILE* fp) {
	if (!node) {
		return;
	}

	// Since a inorder traveling lists data ordered, 
	// it occurs one-sided tree(same with linked list) when the file is uploaded next time
	// By a pre-order traveling, reduce balancing works when the file is uploded next time.
	// If the sorted file is needed, only change pro-order to inorder like listAllData()
	fprintf(fp, "%s,%s,%s", getFirstName(node->data), getLastName(node->data), getMobile(node->data));
	listAllDataToFile(node->left, fp);
	listAllDataToFile(node->right, fp);
}

BTreeNode_ptr removeContact(BTreeNode_ptr tree, char* firstName, char*lastName, int* successed) {
	if (!(tree)) {
		return tree;
	}
	// if the keyword is bigger than the one in current node
	if (strcmp(firstName, getFirstName(tree->data)) > 0) {
		tree->right = removeContact(tree->right, firstName, lastName, successed);
	}
	// if the keyword is smaller than the one in current node
	else if (strcmp(firstName, getFirstName(tree->data)) < 0) {
		tree->left = removeContact(tree->left, firstName, lastName, successed);
	}
	else {
		if (strcmp(lastName, getLastName(tree->data)) > 0) {
			tree->right = removeContact(tree->right, firstName, lastName, successed);
		}
		// if the keyword is smaller than the one in current node
		else if (strcmp(lastName, getLastName(tree->data)) < 0) {
			tree->left = removeContact(tree->left, firstName, lastName, successed);
		}
		else {
			// current node including same keyword
			BTreeNode_ptr cNode = tree;
			*successed = TRUE;

			// if current node has both left and right sub trees
			if ((tree->left) && (tree->right)) {
				BTreeNode_ptr parent = tree->left;
				tree = parent->right;
				if (tree) {
					// get the biggest node in its left sub tree
					while (tree->right) {
						parent = tree;
						tree = tree->right;
					}
					// replace the current node with the biggest node.
					parent->right = tree->left;
					tree->left = cNode->left;
				}
				else {
					tree = parent;
				}
				tree->right = cNode->right;

			}
			// if current node has only a left sub tree
			else if (tree->left) {
				tree = tree->left;
			}
			// if current node has only a right sub tree
			else if (tree->right) {
				tree = tree->right;
			}
			else {
				freeNode(tree);
				return NULL;
			}
		}
	}
	return tree;
}

void freeNode(BTreeNode_ptr tree) {
	free(tree->data->firstName);
	free(tree->data->lastName);
	free(tree->data->mobile);
	free(tree->data);

	free(tree->left);
	free(tree->right);
	free(tree);
}

char* toUpperStr(char* str) {
	char* lowStr = str;
	while (*lowStr) {
		*lowStr = toupper((unsigned char)* lowStr);
		lowStr++;
	}

	return str;
}
