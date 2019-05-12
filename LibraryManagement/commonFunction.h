#pragma once
#include "LibraryManagement.h"

int getNumberPressKey(int MAX, int MIN = 0);

bool isLeapYear(int Year);

int numDaysOfMonth(int Month, int Year);

bool isPossibleDay(int Day, int Month, int Year);

int plusOneIntoAChar(char &numch);
bool plusOneIntoAString(char* &numStr);

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
NodeReader *InitNode(const Readers *data = new Readers());
//======================================================
	
NodeReader *fAddAtTail(LLNodeReader *&ls, Readers *data); // Thêm vào cuối danh sách một struct >> Readers
void printfLLNodeReader(const LLNodeReader *&lsReader);
Readers *findReaderAtNumberic(const LLNodeReader *&lsReader, const int &numberic);

//=============================================================================================
//=============================================================================================