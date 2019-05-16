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

int printUserMenu(int typeAccount);

int printfMenuReaderManagement();

int printfSubMenuReaderManagement();

int editInfReaderMenu();