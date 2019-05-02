#pragma once
#include "LibraryManagement.h"

int getNumberPressKey(int MAX);

bool isLeapYear(int Year);

int numDaysOfMonth(int Month, int Year);

bool isPossibleDay(int Day, int Month, int Year);

int plusOneIntoAChar(char &numch);
bool plusOneIntoAString(char* numStr);

Day getExpiredDay(Day orginDay);
Day getToday();

bool isNumber(char c);

void textBgColor(int colorText, int colorBG);

// bool getInfWithNote(, char *note){

// }
