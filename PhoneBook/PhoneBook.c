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
			continue;
		}


		switch (input[1]) {
		case 'r': 
			toUpperCase(input);
			if (parseRetrieve(root, input + 2)) {
				ifchanged = TRUE;
			}
			break;
		case 's':
			if (showAllList(root)) {
				ifchanged = TRUE;
			}
			break;
		case 'a':
			toUpperCase(input);
			if (parseAdd(root, input + 2)) {
				ifchanged = TRUE;
			}
			printAtXY(4, 32, "Going to main back after 2 secs");
			holdTwoSecs();
			break;
		case 'l':
			if (loadContact(&root, input + 2)) {
				ifchanged = TRUE;
				printAtXY(4, 31, "Successed. Going to main back after 2 secs");
			}
			else {
				printAtXY(4, 31, "Failed. Going to main back after 2 secs");
			}
			holdTwoSecs();
			break;
		case 'w':
			saveToFile(root, input + 2);
			printAtXY(4, 32, "Going to main back after 2 secs");
			holdTwoSecs();
			break;
		case 'e':
			free(input);
			exitProgram(root, ifchanged);
		}
		drawMain();
		writeLoading();
		writeHowtoUse();
		initUserCommandLine();

	}

	free(input);
	input = malloc(MAX_LENGTH);
	return TRUE;
}

int parseRetrieve(BTreeNode_ptr root, char* keyword) {

	// contacts retrieved
	char* list = (char*)malloc(MAX_LENGTH);
	// for illustrating on the screen
	char* result = (char*)malloc(MAX_LENGTH);

	// line number to be drawn
	int lineN = 0;

	if (strlen(keyword) < 1) {
		strcpy(result, "Keyword is not entered.\nGoing to main back after 2 secs");
		printRetrivingResult(result);
		holdTwoSecs();

		free(result);

		return FALSE;
	}
	strcpy(list, "");
	strcpy(result, "The result of searching by ");
	strcat(result, keyword);
	strcat(result, "\n \n");

	searchByFirstName(root, keyword, list);

	// any result
	if (strlen(list)>1) {
		strcat(result, list);
		// print result and additional menus(edit/delete/back)
		lineN = printRetrivingResult(result);
	}
	// no result with the keyword
	else {
		strcpy(result, "Can't search any information with the keyword.\nGoing to main back after 2 secs");
		printRetrivingResult(result);
		holdTwoSecs();
		free(result);
		return FALSE;
	}

	free(result);

	return parserForEditDelete(root, lineN);
}
int parserForEditDelete(BTreeNode_ptr root, int lineN) {

	int ifchanged = FALSE;
	char* input = malloc(MAX_LENGTH);

	int result = FALSE;

	// edit / delete / back to main
	gets(input);

	if (input[0] != '-' ||
		!(input[1] == 'e' || input[1] == 'd' || input[1] == 'b')) {
		return FALSE;
	}

	// change name to uppercase
	toUpperCase(input);

	switch (input[1]) {
	case 'e':
		result = parseEdit(&root, input + 2);
		break;
	case 'd':
		result = parseDelete(root, input + 2);
		break;
	case 'b':
		drawMain();
		writeHowtoUse();
		initUserCommandLine();
		return TRUE;
	}

	free(input);
	
	lineN++;
	if (result == TRUE) {
		printAtXY(4, ++lineN, "Data change successed.");
		printAtXY(4, ++lineN, "Going to main back after 2 secs");
	}
	else {
		printAtXY(4, ++lineN, "Failed your request. ");
		printAtXY(4, ++lineN, "Going to main back after 2 secs");
	}
	holdTwoSecs();
	return result;
}
int parseEdit(BTreeNode_ptr* root, char* keyword) {
	// first name, last name, mobile are seperated by ','
	const char* delim1 = ",";
	// contact before and after are seperated by '/'
	const char* delim2 = "/";

	char* before = strtok(keyword, delim2);
	char* after = strtok(NULL, delim2);

	if (!before || !after) {
		return FALSE;
	}

	char* bFirstName = strtok(before, delim1);
	char* bLastName = strtok(NULL, delim1);

	char* aFirstName = strtok(after, delim1);
	char* aLastName = strtok(NULL, delim1);
	char* aMobile = strtok(NULL, delim1);

	if (!bFirstName || !bLastName || !aFirstName || !aLastName || !aMobile) {
		return FALSE;
	}

	int successed = FALSE;

	// 1. Name will be edited(deleted) should be existed
	// 2. Name will be added shouldn't be existed
	//    or two names are same(only mobile is changed)
	if (ifFullNameIsExisted(*root, bFirstName, bLastName) 
		&& ((!ifFullNameIsExisted(*root, aFirstName, aLastName))
			||(strcmp(bFirstName, aFirstName) == 0 && strcmp(bLastName, aLastName) == 0))) {
		Contact_ptr contact = createContact(aFirstName, aLastName, aMobile);
		// insert the new contact
		*root = insertPhoneBook(*root, contact);
		// remove the existed contact
		*root = removeContact(*root, bFirstName, bLastName, &successed);
		return TRUE;
	}

	return FALSE;
}
int parseDelete(BTreeNode_ptr root, char* keyword) {
	const char* delim = ",";

	char* firstName = strtok(keyword, delim);
	char* lastName = strtokNext;

	if (!firstName || !lastName) {
		return FALSE;
	}

	int successed = FALSE;

	root = removeContact(root, firstName, lastName, &successed);

	return successed;
}

int showAllList(BTreeNode_ptr root) {
	char* result = (char*)malloc(MAX_LENGTH);
	int lineN = 0;
	strcpy(result, "List All of contacts\n\n");
	
	listAllData(root, result);
	lineN = printRetrivingResult(result);

	// additional menus are possible to be used in show all list menu
	return parserForEditDelete(root, lineN);
}

int parseAdd(BTreeNode_ptr root, char* input) {
	// format: firstname(min 1),lastname(min 1),mobile(min 1)

	if (strlen(input) < 5) {
		printAtXY(4, 31, "The input entered is too short.");
		return FALSE;
	}

	// add 'n' to the end of mobile 
	if (input[strlen(input) - 1] != '\n') {
		strcat(input, "\n");
	}

	Contact_ptr contact = strtokContact(input);
	
	if (!contact) {
		printAtXY(4, 31, "The input entered is not valid.");
		return FALSE;
	}
	
	// Two identical full name cannot be saved.
	if(ifFullNameIsExisted(root, getFirstName(contact), getLastName(contact))){
		printAtXY(4, 31, "A same full name is existed.");
		return FALSE;
	}

	root = insertPhoneBook(root, contact);

	printAtXY(4, 31, "The new contact is saved successfully.");
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
		
		Contact_ptr contact = strtokContact(buffer);

		// wrong data is skipped
		if (strtokNext || !contact) {
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
		printAtXY(4, 31, "The file is not usable.");
		return FALSE;
	}

	listAllDataToFile(root, outputFile);

	fclose(outputFile);
	printAtXY(4, 31, "Every information is saved to the file.");
	return TRUE;
}

void exitProgram(BTreeNode_ptr root, int ifchanged) {
	exitMessage(ifchanged);

	if (ifchanged == TRUE) {
		saveToFile(root, "contacts.txt");
	}
	exit(0);
}

void toUpperCase(char* input) {
	int slen = strlen(input);
	for (int i = 2;i < slen;i++) {
		if (input[i] >= 'a' && input[i] <= 'z') {
			input[i] = toupper(input[i]);
		}
	}
}




