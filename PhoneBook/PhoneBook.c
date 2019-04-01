#include "PhoneBook.h"

int main(int argc, char* argv[])
{
	setWindowSize();
	drawMain();
	writeLoading();

	BTreeNode_ptr root = NULL;

	loadContact(&root, "contacts.txt");

	writeHowtoUse();
	initUserCommandLine();

	parser(root);

	listAllData(root);

	return TRUE;
}

int parser(BTreeNode_ptr root) {
	
	int ifchanged = FALSE;
	char* input = malloc(MAX_LENGTH);

	while (TRUE) {
		gets(input);

		if (input[0] != '-' ||
			!(input[1] == 'r' || input[1] == 's' || input[1] == 'a' ||
				input[1] == 'l' || input[1] == 'w' || input[1] == 'e')) {
			return FALSE;
		}

		initUserCommandLine();
		switch (input[1]) {
		case 'r':
			if (parseRetrieve(root, input + 2)) {
				ifchanged = TRUE;
			}
			break;
		case 's':
			break;
		case 'a':
			if (parseAdd(root, input + 2)) {
				ifchanged = TRUE;
			}
			break;
		case 'l':
			if (loadContact(&root, input + 2)) {
				ifchanged = TRUE;
			}
			break;
		case 'w':
			return saveToFile(root, input + 2);
		case 'e':
			free(input);
			exitProgram(root, ifchanged);
		}
	}

	free(input);
	input = malloc(MAX_LENGTH);
	return TRUE;
}

int parserForEditDelete(BTreeNode_ptr root) {
	int ifchanged = FALSE;
	char* input = malloc(MAX_LENGTH);

	gets(input);

	if (input[0] != '-' ||
		!(input[1] == 'e' || input[1] == 'd' || input[1] == 'b')) {
		return FALSE;
	}

	initUserCommandLine();
	switch (input[1]) {
	case 'e':
		break;
	case 'd':

		break;
	case 'b':
		system("cls");
		drawMain();
		writeHowtoUse();
		initUserCommandLine();
		break;
	}
}

int parseRetrieve(BTreeNode_ptr root, char* keyword) {

	char* result = (char*)malloc(MAX_LENGTH);
	strcpy(result, "The result of searching by ");
	strcat(result, keyword);
	strcat(result, "\n\n");

	searchByFirstName(root, keyword, result);

	if (strlen(result)>1) {
		printRetrivingResult(result);
	}

	//print and edit/delete menu
	parserForEditDelete(root);

	return TRUE;

}

int parseAdd(BTreeNode_ptr root, char* input) {
	// format: firstname(min 1),lastname(min 1),mobile(min 1)

	if (strlen(input) < 5) {
		return FALSE;
	}

	Contact_ptr contact = strtokContact(input);
	if (!contact) {
		return FALSE;
	}

	root = insertPhoneBook(root, contact);

	return TRUE;
}

Contact_ptr strtokContact(char* input) {
	
	const char* delim = ",";

	char* firstName = strtok(input, delim);
	char* lastName = strtokNext;
	char* mobile = strtokNext;

	return createContact(firstName, lastName, mobile);
}

int loadContact(BTreeNode_ptr* root, char* filename) {

	FILE* inputFile = fopen(filename, "r");
	if (inputFile == NULL) {
		printf("Error, couldn't load the file: %s\n", filename);
		return FALSE;
	}

	char* buffer = (char*)malloc(MAX_LENGTH);

	while (fgets(buffer, MAX_LENGTH, inputFile)) {
		//printf("%d: %s\n", cnt++, buffer);
		
		Contact_ptr contact = strtokContact(buffer);

		if (strtokNext || !contact) {
			//printf("Error, \"%s\" is wrong. It will be skipped", buffer);
			free(buffer);
			buffer = (char*)malloc(MAX_LENGTH);
			continue;
		}

		*root = insertPhoneBook(*root, contact);
		free(buffer);
		buffer = (char*)malloc(MAX_LENGTH);
	}

	fclose(inputFile);
	return TRUE;
}

int saveToFile(BTreeNode_ptr root, char* filename) {

	FILE* outputFile = fopen(filename, "w");
	if (!outputFile) {
		return FALSE;
	}

	listAllDataToFile(root, outputFile);

	fclose(outputFile);
	return TRUE;
}

void exitProgram(BTreeNode_ptr root, int ifchanged) {
	exitMessage(ifchanged);

	if (ifchanged == TRUE) {
		saveToFile(root, "contacts.txt");
	}
	exit(0);
}




