#pragma once
#include "LibraryManagement.h"

#if defined(_WIN32) || defined(_WIN64)
	void textBgColor(int colorText, int colorBG);
#else 
	void textBgColor(int colorText, int colorBG);
#endif

int getNumberPressKey(int MAX, int MIN);

bool isLeapYear(int Year);

int numDaysOfMonth(int Month, int Year);

bool isPossibleDay(int Day, int Month, int Year);

void getUsername(char username[]);

void getBirthday(Day &birthday);

void getNationalID(char nationID[]);

void getSex(int &sex);

void getStatus(bool &status);

void getTypeAccount(Users &A);

void getReaderID(char ID[]);

int wantEdit();

char *toStr(long n);

Day getExpiredDay(Day orginDay);

Day getToday();

bool isNumber(char c);

Day getDayFrmUser();

// void textBgColor(int colorText, int colorBG);

void printfDay(Day day);

char *getStringFrmUser(char *note);

int getNumber(char *note);

int plusOneIntoAChar(char &numch);
bool plusOneIntoAString(char *numStr);
