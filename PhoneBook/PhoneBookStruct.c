#include "PhoneBookStruct.h"

struct contact {
	char* firstName;
	char* lastName;
	char* mobile;
};

struct bTreeNode {
	Contact_ptr data;
	struct bTreeNode* left;
	struct bTreeNode* right;
};

BTreeNode_ptr insertPhoneBook(BTreeNode_ptr tree, Contact_ptr contact) {

	if (!tree) {
		tree = createNode();
		setData(tree, contact);
	}
	else if (strcmp(contact->firstName, getFirstName(tree)) < 0) {
		tree->left = insertPhoneBook(tree->left, contact);
		tree = rebalance(tree);
	}
	else if (strcmp(contact->firstName, getFirstName(tree)) > 0) {
		tree->right = insertPhoneBook(tree->right, contact);
		tree = rebalance(tree);
	}
	else {
		if (strcmp(contact->lastName, getLastName(tree)) < 0) {
			tree->left = insertPhoneBook(tree->left, contact);
			tree = rebalance(tree);
		}
		else if (strcmp(contact->lastName, getLastName(tree)) >= 0) {
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

BTreeNode_ptr searchByFirstName(BTreeNode_ptr node, char* firstName, char* result) {

	// current node
	BTreeNode_ptr cNode = node;
	char* cFirstname;

	while (cNode != NULL) {
		cFirstname = getFirstName(cNode);

		if (strcmp(firstName, cFirstname) == 0) {
			//look for same name
			lookForSameName(cNode, firstName, result);
			return cNode;
		}
		else if (strcmp(firstName, cFirstname) < 0) {
			cNode = getLNode(cNode);
		}
		else {
			cNode = getRNode(cNode);
		}
	}
	return NULL;
}
void lookForSameName(BTreeNode_ptr node, char* firstName, char* result) {

	if (!node) {
		return;
	}

	BTreeNode_ptr cNode = node;
	char* cFirstname = getFirstName(node);

	if (strcmp(firstName, cFirstname) == 0) {
		lookForSameName(node->left, firstName, result);
		getContact(node, result);
		lookForSameName(node->right, firstName, result);
	}
	else if (strcmp(firstName, cFirstname) < 0) {
		lookForSameName(node->left, firstName, result);
	}
	else {
		lookForSameName(node->right, firstName, result);
	}
	
}

BTreeNode_ptr searchByLastName(BTreeNode_ptr node, char* lastName, char** result) {

	// current node
	BTreeNode_ptr cNode = node;
	char* cLastname;

	while (cNode != NULL) {
		cLastname = getLastName(cNode);

		if (strcmp(lastName, cLastname) == 0) {
			return cNode;
		}
		else if (strcmp(lastName, cLastname) < 0) {
			cNode = getLNode(cNode);
		}
		else {
			cNode = getRNode(cNode);
		}
	}
	return NULL;
}
BTreeNode_ptr searchByMobile(BTreeNode_ptr node, char* mobile, char** result) {

	// current node
	BTreeNode_ptr cNode = node;
	char* cMobile;

	while (cNode != NULL) {
		cMobile = getMobile(cNode);

		if (strcmp(mobile, cMobile) == 0) {
			return cNode;
		}
		else if (strcmp(mobile, cMobile) < 0) {
			cNode = getLNode(cNode);
		}
		else {
			cNode = getRNode(cNode);
		}
	}
	return NULL;
}

void getContact(BTreeNode_ptr node, char* str) {
	char* contact = (char*)malloc(1000);
	sprintf(contact, "%s %s: %s", node->data->firstName, node->data->lastName, node->data->mobile);
	strcat(str, contact);
	free(contact);
}

char* getFirstName(BTreeNode_ptr node) {
	return node->data->firstName;
}
char* getLastName(BTreeNode_ptr node) {
	return node->data->lastName;
}
char* getMobile(BTreeNode_ptr node) {
	return node->data->mobile;
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
	parent->left = getRNode(child); // connect right a subnode of child node to a left subnode of parent
	child->right = parent; // connect parent node to a right subnode of child node

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
	parent->right = getLNode(child); //connect a left subnode of child node to a left subnode of parent
	child->left = parent; // connect parent node to left a subnode of child node

	return child;
}
BTreeNode_ptr rotate_right_left(BTreeNode_ptr node) {
	BTreeNode_ptr parent = node;
	BTreeNode_ptr child = getRNode(parent);

	parent->right = rotate_right(child); // rotate its child tree to the right
	return rotate_left(parent); // rotate the tree to the left
}

BTreeNode_ptr rebalance(BTreeNode_ptr root) {
	int hDiff = calHDiff(root);

	if (hDiff >= 2) {
		if (calHDiff(getLNode(root)) > 0) {
			root = rotate_right(root);
		}
		else {
			root = rotate_left_right(root);
		}
	}
	if (hDiff <= -2) {
		if (calHDiff(getRNode(root)) < 0) {
			root = rotate_left(root);
		}
		else {
			root = rotate_right_left(root);
		}
	}

	return root;
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

void listAllData(BTreeNode_ptr node, int num) {
	if (!node) {
		return;
	}

	listAllData(node->left, num);
	printf("%d. %s %s: %s",num++, getFirstName(node), getLastName(node), getMobile(node));
	listAllData(node->right, num);
}

void listAllDataToFile(BTreeNode_ptr node, FILE* fp) {
	if (!node) {
		return;
	}

	listAllDataToFile(node->left, fp);
	fprintf(fp, "%s,%s,%s", getFirstName(node), getLastName(node), getMobile(node));
	listAllDataToFile(node->right, fp);
}

BTreeNode_ptr removeContact(BTreeNode_ptr tree, char* firstName, char*lastName) {
	if (!(tree)) {
		return tree;
	}
	// if the keyword is bigger than the one in current node
	if (strcmp(firstName, getFirstName(tree)) > 0) {
		tree->right = removeContact(tree->right, firstName, lastName);
	}
	// if the keyword is smaller than the one in current node
	else if (strcmp(firstName, getFirstName(tree)) < 0) {
		tree->left = removeContact(tree->left, firstName, lastName);
	}
	else {
		if (strcmp(lastName, getLastName(tree)) > 0) {
			tree->right = removeContact(tree->right, firstName, lastName);
		}
		// if the keyword is smaller than the one in current node
		else if (strcmp(lastName, getLastName(tree)) < 0) {
			tree->left = removeContact(tree->left, firstName, lastName);
		}
		else {
			// current node including same keyword
			BTreeNode_ptr cNode = tree;

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
			free(cNode);
		}
	}
	return tree;
}

/*
BTreeNode_ptr removeContact(BTreeNode_ptr tree, Contact_ptr contact) {
	if (!(tree)) {
		return tree;
	}
	// if the keyword is bigger than the one in current node
	if (strcmp(contact->firstName, getFirstName(tree)) > 0) {
		tree->right = removeContact(tree->right, contact);
	}
	// if the keyword is smaller than the one in current node
	else if (strcmp(contact->firstName, getFirstName(tree)) < 0) {
		tree->left = removeContact(tree->left, contact);
	}
	//// if the keyword is same with the one in current node
	else {
		// current node including same keyword
		BTreeNode_ptr cNode = tree;

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
		free(cNode);
	}
	return tree;
}*/

char* toUpperStr(char* str) {
	char* lowStr = str;
	while (*lowStr) {
		*lowStr = toupper((unsigned char)* lowStr);
		lowStr++;
	}

	return str;
}
