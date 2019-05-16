#pragma once
#include "LibraryManagement.h"

#if defined(_WIN32) || defined(_WIN64)
	void textBgColor(int colorText, int colorBG);

#endif

int getNumberPressKey(int MAX, int MIN);

bool isLeapYear(int Year);

int numDaysOfMonth(int Month, int Year);

bool isPossibleDay(int Day, int Month, int Year);

int plusOneIntoAChar(char numch);

bool plusOneIntoAString(char numStr[]);

Day getExpiredDay(Day orginDay);

Day getToday();

bool isNumber(char c);

Day getDayFrmUser();

void textBgColor(int colorText, int colorBG);

void printfDay(Day day);

char *getStringFrmUser(char *note);

int getNumber(char *note);
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// ------------------------------------Link List-----------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

//======================================================
// << Hàm khởi tạo danh sách và node
LLNodeReader *Init();
NodeReader *InitNode(Readers *data);
NodeReader *InitNode();
//======================================================
	
NodeReader *fAddAtTail(LLNodeReader *&ls, Readers *data); // Thêm vào cuối danh sách một struct >> Readers

void printfLLNodeReader(LLNodeReader *lsReader);

Readers *findReaderAtNumberic(LLNodeReader *lsReader, int numberic);

//=============================================================================================
//=============================================================================================