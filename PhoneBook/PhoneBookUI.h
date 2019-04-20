#ifndef PhoneBookUI_H
#define PhoneBookUI_H

#include <stdio.h>
#include <windows.h>

#define WINDOW_X 32
#define WINDOW_Y 41
#define FALSE 0
#define TRUE 1
#define MAX_LENGTH 2000

void setWindowSize();
void printAtXY(int x, int y, char* s);
void drawMain();
void drawBorder();
void writeTitle();
void writeLoading();
void initUserCommandLine();
int printRetrivingResult(char* result);
void printEDMenu(int* lineN);
void exitMessage(int ifchanged);
void holdTwoSecs();
#endif