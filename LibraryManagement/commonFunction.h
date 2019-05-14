#pragma once
#include "LibraryManagement.h"

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

char *toStr(long n);

Day getExpiredDay(Day orginDay);

Day getToday();

bool isNumber(char c);

Day getDayFrmUser();

void textBgColor(int colorText, int colorBG);

void printfDay(Day day);

char *getStringFrmUser(char *note);

int getNumber(char *note);
