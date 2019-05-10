#include "commonFunction.h"
#include "time.h"

//Hàm kiểm tra số nhập từ bàn phím
int getNumberPressKey(int MAX, int MIN = 0){
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
			if (ch >= MIN + '0' && ch <= int(max) + '0')
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

	return int(ch - '0');
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



// cong 1 vao mot chuoi so -> dung de sinh ma so lien tuc
int plusOneIntoAChar(char &numch){
	if (numch < '0' && numch > '9')
	{
		return -1;
	}
	else if (numch == '9')
	{
		numch = '0';
		return 1;
	}
	else {
		numch += 1;
		return 0;
 	}
}
bool plusOneIntoAString(char* &numStr){

	int length = strlen(numStr) -1;
	while (length >= 0){
		switch(plusOneIntoAChar(numStr[length])){
			case -1:
				return false;
				break;
			case 0:
				length = -1;
				break;
		}
		length--;
	}

	return true;
}

Day getExpiredDay(Day orginDay){ 

	Day plusDay;
	plusDay = orginDay;
	plusDay.Date += _MAX_DAY_EXPIRES_;

	while (!isPossibleDay(plusDay.Date, plusDay.Month, plusDay.Year)){
		if (plusDay.Date > numDaysOfMonth(plusDay.Month, plusDay.Year))
		{
			plusDay.Date -= numDaysOfMonth(plusDay.Month, plusDay.Year);
			if ((++plusDay.Month) > 12)
			{
				plusDay.Month = 1;
				plusDay.Year++;
			}
		}
	}

	return plusDay;

}

Day getToday(){
    time_t rawtime;
    struct tm * timeinfo; // khai bao mot con tro cua struct thoi gian

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );


    fprintf(stdout, "[%d %d %d %d:%d:%d]",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    Day days;
    days.Date 	= timeinfo->tm_mday;
    days.Month 	= timeinfo->tm_mon + 1;
    days.Year 	= timeinfo->tm_year + 1900;

    return days;
}

bool isNumber(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

Day getDayFrmUser(){
	Day day;
	do
	{
		printf("Nhap ngay: ");
		scanf("%d", &day.Date);
		int temp = getchar();

		printf("Nhap thang: ");
		scanf("%d", &day.Month);
		temp = getchar();

		printf("Nhap nam: ");
		scanf("%d", &day.Year);
		temp = getchar();

		if (!isPossibleDay(day.Date, day.Month, day.Year))
			printf("Ngay thang nam sinh khong hop le vui long nhap lai.\n");
		else break;
	} while (1);
	return day;
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

void printfDay(Day day){
	printf("%d/ %d / %d\n", day.Date, day.Month, day.Year);
}

char *getStringFrmUser(char *note){
	printf("%s:\t", note);
	char *strGet = new char();
	int getEnter = getchar();
	gets(strGet);

	return strGet;
}

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// ------------------------------------Link List-----------------------------------------------
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

//======================================================
// << Hàm khởi tạo danh sách và node
LLNodeReader *Init(){
	LLNodeReader *ls = new LLNodeReader();
	ls->pHead = NULL;
	ls->pTail = NULL;
	checkNull(ls);
	return ls;
}
NodeReader *InitNode(const Readers *data){
	NodeReader *no = new NodeReader();
	no->pNext = new NodeReader();
	no->pPrev = new NodeReader();
	*no->reader = *data;

	return no;
}
//======================================================
	
NodeReader *fAddAtTail(LLNodeReader *ls, const Readers *data){ // Thêm vào cuối danh sách một struct >> Readers
	NodeReader *no = InitNode(data);
	if (no == NULL)
	{
		return NULL;
	}

	// Tạo liên kết
	no->pPrev = ls->pTail; 
	no->pNext = NULL;
	if (ls->pTail == NULL) // nếu danh sách rỗng
	{
		ls->pHead = no;
	}
	else {
		ls->pTail->pNext = no;
	}
	ls->pTail = no;

	return no;
}

//=============================================================================================
//=============================================================================================
