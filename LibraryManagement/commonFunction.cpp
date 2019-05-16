#include "commonFunction.h"
#include "createUser.h"
#include "time.h"
#include "readerManagement.h"

//Hàm kiểm tra số nhập từ bàn phím
int getNumberPressKey(int MAX, int MIN){
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
			if (ch >= char(MIN + '0') && ch <= char(max + '0'))
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

// Hàm nhập Username
void getUsername(char username[])
{
	do
	{
		flushall();
		printf("Nhap Username (toi da 20 ky tu): ");
		gets(username);
		flushall();

		if (!checkUsername(username))
			printf("Username da ton tai. Vui long nhap Username khac.\n");
	} while (!checkUsername(username));
}

// Hàm nhập Ngày sinh
void getBirthday(Day &birthday)
{
	bool checkDay;
	do
	{
		flushall();
		printf("Nhap ngay sinh: ");
		scanf("%d", &birthday.Date);
		flushall();

		printf("Nhap thang sinh: ");
		scanf("%d", &birthday.Month);
		flushall();

		printf("Nhap nam sinh: ");
		scanf("%d", &birthday.Year);
		flushall();

		checkDay = isPossibleDay(birthday.Date, birthday.Month, birthday.Year);
		if (!checkDay)
			printf("Ngay thang nam sinh khong hop le vui long nhap lai.\n");
	} while (checkDay == false);
}

// Hàm nhập CMND
void getNationalID(char nationID[])
{
	int flag = 0;
	do
	{
		flushall();
		printf("Nhap CMND (9 so hoac 12 so): ");
		gets(nationID);
		flushall();

		int i;
		if (strlen(nationID) != 9 && strlen(nationID) != 12)
		{
			printf("CMND khong hop le. Vui long nhap lai.\n");
			continue;
		}

		flag = 1;

		for (int i = 0; i < strlen(nationID); i++)
		{
			if (!isNumber(nationID[i]))
			{
				flag = 0;
				printf("CMND khong hop le. Vui long nhap lai.\n");
				break;
			}
		}
	} while (flag == 0);

}

// Hàm nhập giới tính
void getSex(int &sex)
{
	do
	{
		flushall();
		printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
		scanf("%d", &sex);
		int temp = getchar();

		if (sex != 0 && sex != 1)
			printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
	} while (sex != 0 && sex != 1);
}

// Hàm nhập tình trạng
void getStatus(bool &status)
{
	do
	{
		flushall();
		printf("Nhap tinh trang (Actived nhap 1; Blocked nhap 0): ");
		scanf("%d", &status);
		int temp = getchar();

		if (status != 0 && status != 1)
			printf("Vui long nhap lai. Actived nhap 1, Blocked nhap 0.\n");
	} while (status != 0 && status != 1);
}

// Hàm nhập phân quyền
void getTypeAccount(Users &A)
{
	do
	{
		flushall();
		printf("Nhap phan quyen (Chuyen vien nhap 2; quan ly nhap 3): ");
		scanf("%d", &A.typeAccount);
		int temp = getchar();

		if (A.typeAccount != 2 && A.typeAccount != 3)
			printf("Vui long nhap lai. Chuyen vien nhap 2; quan ly nhap 3.\n");
	} while (A.typeAccount != 2 && A.typeAccount != 3);
}

// Hàm nhập ID độc giả
void getReaderID(char ID[])
{
	int flag = 0;
	do
	{
		flushall();
		printf("Nhap ma doc gia (8 so): ");
		gets(ID);
		flushall();

		int i;
		if (strlen(ID) != 8)
		{
			printf("Ma doc gia khong hop le. Vui long nhap lai.\n");
			continue;
		}

		flag = 1;

		for (int i = 0; i < strlen(ID); i++)
		{
			if (!isNumber(ID[i]))
			{
				flag = 0;
				printf("Ma doc gia khong hop le. Vui long nhap lai.\n");
				break;
			}
		}
	} while (flag == 0);

}

// Hàm nhập ISBN sách
void getISBN(char *ISBN)
{
	int flag = 0;
	do
	{
		flushall();
		printf("Nhap ISBN: ");
		gets(ISBN);

		int i;
		if (strlen(ISBN) != 13)
		{
			printf("ISBN phai co 13 chu so. Vui long nhap lai.\n");
			continue;
		}

		flag = 1;

		for (int i = 0; i < strlen(ISBN); i++)
		{
			if (!isNumber(ISBN[i]))
			{
				flag = 0;
				printf("ISBN khong hop le. Vui long nhap lai.\n");
				break;
			}
		}
	} while (flag == 0);
}

// Hàm hỏi người dùng muốn chỉnh sửa nữa không?
int wantEdit()
{
	int edit;
	printf("Ban con muon chinh sua nua khong? Nhap 0 (Khong), Nhap 1 (Co): ");
	do
	{
		scanf("%d", &edit);
		if (edit == 1)
			return 1;
		else if (edit == 0)
			return 0;
		else
			printf("Vui long nhap 0 hoac 1\n");
	} while (edit != 0 && edit != 1);
}

// Hàm hỏi muốn mượn sách nữa không?
int wantBorrow()
{
	int borrow;
	printf("Doc gia nay con muon muon them sach nua khong? Nhap 0 (Khong), Nhap 1 (Co): ");
	do
	{
		scanf("%d", &borrow);
		if (borrow == 1)
			return 1;
		else if (borrow == 0)
			return 0;
		else
			printf("Vui long nhap 0 hoac 1\n");
	} while (borrow != 0 && borrow != 1);
}

//Tạo chuỗi mã độc giả
char *toStr(long n)
{
	char str[9];
	sprintf(str, "%ld", n);
	char S[9];
	S[0] = '\0';
	int count = 8 - strlen(str);
	while (count > 0)
	{
		strcat(S, "0");
		count--;
	}
	strcat(S, str);
	S[8] = '\0';
	return S;
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


    fprintf(stdout, "[%d/%d/%d %d:%d:%d]\n",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

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

int getNumber(char *note){
	printf("%s\n", note);
	int x = 0;
	scanf("%d", &x);
	return x;
}

