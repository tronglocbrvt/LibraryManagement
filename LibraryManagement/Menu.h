#pragma once
#include "LibraryManagement.h"

void resizeConsole(int width, int height);

void gotoxy(int x, int y);

int printLoginMenu();

void printfMainMenu();

int printUserMenu(int typeAccount);

int printfMenuReaderManagement();

int printfSubMenuReaderManagement();

int editInfReaderMenu();