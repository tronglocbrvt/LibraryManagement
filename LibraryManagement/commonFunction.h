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

void getNationalID(char nationID[]); // Nhập CMND người dùng

void getSex(int &sex); //  Nhập giới tính người dùng

void getStatus(bool &status); // Nhập trạng thái người dùng

void getTypeAccount(Users &A); // Nhập phân quyền người dùng

void getReaderID(char ID[]); // Nhập mã đọc giả

void getISBN(char *ISBN); // Nhập ISBN sách

int wantEdit();

int wantBorrow();

char *toStr(long n);

Day getExpiredDay(Day orginDay);

Day getToday();

bool isNumber(char c);

Day getDayFrmUser();

void printfDay(Day day);

char *getStringFrmUser(char *note);

int getNumber(char *note);

int plusOneIntoAChar(char &numch);
bool plusOneIntoAString(char *numStr);
