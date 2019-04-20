#include "PhoneBookUI.h"

void setWindowSize() {
	system("mode con cols=64 lines=41");
}

void printAtXY(int x, int y, char* s) {
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", s);
}

void drawMain() {
	drawBorder();
	writeTitle();
}

void drawBorder() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	
	int i;
	for (i = 0;i < WINDOW_X;i++) {
		printAtXY(i, 0, "■");
		printAtXY(i, 1, "■");
	}
	for (i = 1;i < WINDOW_Y - 1;i++) {
		printAtXY(0, i, "■");
		printAtXY(1, i, "■");
		printAtXY(WINDOW_X - 2, i, "■");
		printAtXY(WINDOW_X - 1, i, "■");
	}
	for (i = 0;i < WINDOW_X;i++) {
		printAtXY(i, WINDOW_Y - 1, "■");
		printAtXY(i, WINDOW_Y - 2, "■");
	}
}

void writeTitle() {

	// color green
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

	// first row
	printAtXY(4, 3, "■");
	printAtXY(5, 3, "■");
	printAtXY(6, 3, "■");
	printAtXY(9, 3, "■");
	printAtXY(12, 3, "■");
	printAtXY(15, 3, "■");
	printAtXY(16, 3, "■");
	printAtXY(19, 3, "■");
	printAtXY(22, 3, "■");
	printAtXY(24, 3, "■");
	printAtXY(25, 3, "■");
	printAtXY(26, 3, "■");
	printAtXY(27, 3, "■");

	// second row
	printAtXY(4, 4, "■");
	printAtXY(7, 4, "■");
	printAtXY(9, 4, "■");
	printAtXY(12, 4, "■");
	printAtXY(14, 4, "■");
	printAtXY(17, 4, "■");
	printAtXY(19, 4, "■");
	printAtXY(20, 4, "■");
	printAtXY(22, 4, "■");
	printAtXY(24, 4, "■");

	// third row
	printAtXY(4, 5, "■");
	printAtXY(7, 5, "■");
	printAtXY(9, 5, "■");
	printAtXY(10, 5, "■");
	printAtXY(11, 5, "■");
	printAtXY(12, 5, "■");
	printAtXY(14, 5, "■");
	printAtXY(17, 5, "■");
	printAtXY(19, 5, "■");
	printAtXY(20, 5, "■");
	printAtXY(22, 5, "■");
	printAtXY(24, 5, "■");
	printAtXY(25, 5, "■");
	printAtXY(26, 5, "■");
	printAtXY(27, 5, "■");

	// fourth row
	printAtXY(4, 6, "■");
	printAtXY(5, 6, "■");
	printAtXY(6, 6, "■");
	printAtXY(9, 6, "■");
	printAtXY(12, 6, "■");
	printAtXY(14, 6, "■");
	printAtXY(17, 6, "■");
	printAtXY(19, 6, "■");
	printAtXY(21, 6, "■");
	printAtXY(22, 6, "■");
	printAtXY(24, 6, "■");

	// fifth row
	printAtXY(4, 7, "■");
	printAtXY(9, 7, "■");
	printAtXY(12, 7, "■");
	printAtXY(14, 7, "■");
	printAtXY(17, 7, "■");
	printAtXY(19, 7, "■");
	printAtXY(21, 7, "■");
	printAtXY(22, 7, "■");
	printAtXY(24, 7, "■");

	// sixth row
	printAtXY(4, 8, "■");
	printAtXY(9, 8, "■");
	printAtXY(12, 8, "■");
	printAtXY(15, 8, "■");
	printAtXY(16, 8, "■");
	printAtXY(19, 8, "■");
	printAtXY(22, 8, "■");
	printAtXY(24, 8, "■");
	printAtXY(25, 8, "■");
	printAtXY(26, 8, "■");
	printAtXY(27, 8, "■");

	// eighth row
	printAtXY(6, 10, "■");
	printAtXY(7, 10, "■");
	printAtXY(8, 10, "■");
	printAtXY(12, 10, "■");
	printAtXY(13, 10, "■");
	printAtXY(17, 10, "■");
	printAtXY(18, 10, "■");
	printAtXY(21, 10, "■");
	printAtXY(24, 10, "■");

	// nineth row
	printAtXY(6, 11, "■");
	printAtXY(9, 11, "■");
	printAtXY(11, 11, "■");
	printAtXY(14, 11, "■");
	printAtXY(16, 11, "■");
	printAtXY(19, 11, "■");
	printAtXY(21, 11, "■");
	printAtXY(23, 11, "■");

	// tenth row
	printAtXY(6, 12, "■");
	printAtXY(7, 12, "■");
	printAtXY(8, 12, "■");
	printAtXY(11, 12, "■");
	printAtXY(14, 12, "■");
	printAtXY(16, 12, "■");
	printAtXY(19, 12, "■");
	printAtXY(21, 12, "■");
	printAtXY(22, 12, "■");

	// eleventh row
	printAtXY(6, 13, "■");
	printAtXY(9, 13, "■");
	printAtXY(11, 13, "■");
	printAtXY(14, 13, "■");
	printAtXY(16, 13, "■");
	printAtXY(19, 13, "■");
	printAtXY(21, 13, "■");
	printAtXY(22, 13, "■");

	// twelveth row
	printAtXY(6, 14, "■");
	printAtXY(9, 14, "■");
	printAtXY(11, 14, "■");
	printAtXY(14, 14, "■");
	printAtXY(16, 14, "■");
	printAtXY(19, 14, "■");
	printAtXY(21, 14, "■");
	printAtXY(23, 14, "■");

	// thirteenth row
	printAtXY(6, 15, "■");
	printAtXY(7, 15, "■");
	printAtXY(8, 15, "■");
	printAtXY(12, 15, "■");
	printAtXY(13, 15, "■");
	printAtXY(17, 15, "■");
	printAtXY(18, 15, "■");
	printAtXY(21, 15, "■");
	printAtXY(24, 15, "■");

	printAtXY(15, 34, "BY");
	printAtXY(13, 36, "HYEWON CHOI");
	printAtXY(12, 37, "JEFFREY ODOGBA");

}

void writeHowtoUse() {

	// color blue
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

	printAtXY(13, 19, "How to use");
	printAtXY(4, 21, "-r retrieve data with followed firstname.");
	printAtXY(4, 22, "-s show all contacts ordered by firstname.");
	printAtXY(4, 23, "-a add new data. firstname,lastname,mobile");
	printAtXY(4, 24, "-l load a following file name.");
	printAtXY(4, 25, "-w write the phone book to a new file.");
	printAtXY(4, 26, "   The name of file is following");
	printAtXY(4, 27, "-e Exit the phone book");
}

void writeLoading() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printAtXY(13, 19, "Loading...");

	Sleep(1000);
}

void initUserCommandLine() {
	// clear the line a user enters their request
	printAtXY(4, 30, "                     ");

	COORD pos = { 8, 30 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

int printRetrivingResult(char* result) {

	drawBorder();

	const char* delim = "\n";
	char* line = strtok(result, delim);
	int lineN = 4;


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	while (line != NULL) {
		printAtXY(4, lineN++, line);
		
		// if the number of data is over than height of screen,
		// print the rest on the next page.
		if (lineN > 33) {
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printAtXY(4, ++lineN, "Press Enter to continue in the next page.");
			
			//buffer clear
			while ((getchar()) != '\n');

			lineN = 4;

			drawBorder();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		}
		line = strtok(NULL, delim);
	}

	// room for additional menu
	if (lineN > 29) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printAtXY(4, ++lineN, "Press Enter to continue in the next page.");

		//buffer clear
		while ((getchar()) != '\n');

		lineN = 3;

		drawBorder();
	}

	line++;
	printEDMenu(&lineN);

	return lineN;
}

void printEDMenu(int* lineN) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

	printAtXY(4, ++(*lineN),  "-e edit data.");
	printAtXY(4, ++(*lineN), "   firstname,lastname/newFirst,newLast,newMobile");
	printAtXY(4, ++(*lineN), "-d delete data.");
	printAtXY(4, ++(*lineN), "   firstname,lastname");
	printAtXY(4, ++(*lineN), "-b back to main menu.");

	printAtXY(4, ++(*lineN), " ");
	printAtXY(4, ++(*lineN), "");
}

void exitMessage(int ifchanged) {
	// if data has been changed
	if (ifchanged == TRUE) {
		printAtXY(4, 31, "Saving changed data");
		Sleep(1000);
	}
	else {
		printAtXY(4, 31, "Thank you for using the phone book.");
		Sleep(1000);
	}
}

void holdTwoSecs() {
	Sleep(2000);
}
