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

void showTitleAnalyzing();
int analyzingMenuForAdmin();
int analyzingMenuForExpert();
int analyzingMenuManager();

void showTitleHeader();
void showFooter();


int analyzingMenuManager();

void showTitleBorrow();
void showTitleReturn();

//>>>>>>>>>>>>>>>>>>>>>>>>. sub meunu title
void showTitleOverdue();
void showTitleListBook();
void showTitleCategory();
void showTitleListReader();
void showTitleMaleReader();
void showTitleFemaleReader();
void showTitleListBorrowing();

//>>>>>>>>>>>>>>>>>>>>>>>> title chức năng reader
void showTitleViewReader();
void showTitleAddNewReader();
void showTitleEditReader();
void showTitleAfterEditReader();
void showTitleDeleteReader();
void showTitleFindReaderByNationId();
void showTitleFindReaderByName();

//>>>>>>>>>>>>>>>>>>>>>>>> title chức năng user
void showTitleCreatUser();
void showTitleDecentraliseUser();
void showTitleChangePassUser();
void showTitleStatusUser();
void showTitleAfterEditUser();

//>>>>>>>>>>>>>>>>>>>>>>>> title chức năng book
void showTitleViewBook();
void showTitleAddNewBook();
void showTitleEditBook();
void showTitleAfterEditBook();
void showTitleDeleteBook();
void showTitleFindBookByISBN();
void showTitleFindBookByName();