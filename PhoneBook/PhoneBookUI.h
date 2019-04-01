#ifndef PhoneBookUI_H
#define PhoneBookUI_H

#include <stdio.h>
#include <windows.h>

#define WINDOW_X 32
#define WINDOW_Y 40
#define FALSE 0
#define TRUE 1

void setWindowSize();
void printAtXY(int x, int y, char* s);
void drawMain();
void drawBorder();
void writeTitle();
void initUserCommandLine();
void printRetrivingResult(char* result);
void printEDMenu();
void exitMessage(int ifchanged);
#endif