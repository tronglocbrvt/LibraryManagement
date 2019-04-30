#include "commonFunction.h"

//Hàm kiểm tra số nhập từ bàn phím
int getNumberPressKey(int MAX){
	int max = (MAX <= 9) ? MAX : 9;
	char ch = ' ';
	printf("Nhan so de chon: ");
	
	while (1) {
			if (kbhit()) {
			ch = getch();
			// Stores the pressed key in ch 
			// printf("ban chon: %c\n", );
			// Terminates the loop 
			// when escape is pressed 
			if (ch >= '0' && ch <= int(max) + 48)
				// if (int(ch) == 27) 
				break; 
			if (ch == 27)
			{
				return -1;
			}
			if (ch == '`')
			{
				return -2;
			}
		}

	}

	return int(ch - 48);
}

// Hàm kiểm tra năm nhuận
bool isLeapYear(int Year)
{
	if ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0)
	{
		return true;
	}
	return false;

}

// Hàm trả về số ngày trong tháng thuộc năm 
int numDaysOfMonth(int Month, int Year)
{
	int numOfDays; // Tổng số ngày

	switch (Month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		numOfDays = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		numOfDays = 30;
		break;
	case 2:
		if (isLeapYear(Year))
		{
			numOfDays = 29;
		}
		else
		{
			numOfDays = 28;
		}
		break;
	}

	return numOfDays;
}

// Hàm kiểm tra ngày dd/mm/yyyy cho trước có phải là ngày hợp lệ
bool isPossibleDay(int Day, int Month, int Year)
{
	// Kiểm tra năm
	if (Year < 0)
	{
		return false; // => Ngày không còn hợp lệ nữa
	}

	// Kiểm tra tháng
	if (Month < 1 || Month > 12)
	{
		return false; // => Ngày không còn hợp lệ nữa
	}

	// Kiểm tra ngày
	if (Day < 1 || Day > numDaysOfMonth(Month, Year))
	{
		return false; // => Ngày không còn hợp lệ nữa
	}

	return true;
}

bool isNumber(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

//Chỉnh màu chữ và màu nền
/*
0 black
1 blue
2 green
3 aqua
4 red
5 purple
6 yellow
7 white
8 gray
9 light blue
10 light green
11 light aqua
12 light red
13 light purple
14 light yellow
15 bright white
*/

void textBgColor(int colorText, int colorBG) // cplusplus
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (colorBG << 4) | colorText);
}
