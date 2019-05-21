#pragma once
#include "LibraryManagement.h"

#if defined(_WIN32) || defined(_WIN32)
 void resizeConsole(int width, int height);
 void gotoxy(int x, int y);
#else 
 void resizeConsole(int width, int height);
 void gotoxy(int x, int y);
#endif
int printLoginMenu();

void printfMainMenu();


void showTitleUser();
int printUserMenu(int typeAccount);

// void drawRectangle(int positionX, int positionY, int width, int height, int color);
void showTitleReader();
int printfMenuReaderManagementForAdmin();
int printfMenuReaderManagementForExpert();
int printfMenuReaderManagementForManager();
int editInfReaderMenu();

void showTitleBook();
int printfMenuBookManagementForAdmin();
int printfMenuBookManagementForExpert();
int printfMenuBookManagementForManager();
int editInfBookMenu();

int askYesNoQuestion(char *note);

int analyzingMenuForAdmin();
int analyzingMenuForExpert();
int analyzingMenuManager();

void showTitleHeader();
void showFooter();


int analyzingMenuManager();

void showTitleBorrow();
void showTitleReturn();