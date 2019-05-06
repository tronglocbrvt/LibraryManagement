#include "Menu.h"
#include "commonFunction.h"

//=================================================
// on window
 void resizeConsole(int width, int height)
 {
 	HWND console = GetConsoleWindow();
 	RECT r;
 	GetWindowRect(console, &r);
 	MoveWindow(console, r.left, r.top, width, height, TRUE);
 }
 void gotoxy(int x, int y)
 {
     static HANDLE h = NULL;  
     if(!h)
         h = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD c = { x, y };  
     SetConsoleCursorPosition(h,c);
 }
//=================================================



int printLoginMenu(){
	 printf("*******************************************\n");
	 gotoxy(10,1);

	// do somthing here: check if username is exist and password is right
	bool checkUsername = 1;
	bool checkPassword = 1;

	if (checkUsername && checkPassword)
	{
		system("cls");
		printfMainMenu();
		return getNumberPressKey(MAX_CHOICE);
		// return value which user type which will be built in commonFunction.h

	}
	else {
		printf("Tai khoan khong ton tai!\n");
		// waitfor press enter: getchar()
		return printLoginMenu();
	}

}

void printfMainMenu(){
	printf("1. Quan ly tai khoan ca nhan.\n");
	printf("2. Quan ly doc gia.\n");
	printf("3. Quan ly sach.\n");
	printf("4. Lap phieu muon sach.\n");
	printf("5. Lap phieu tra sach.\n");
	printf("6. Thong ke co ban.\n");
	printf("7. Dang xuat.\n");
	printf("0. Thoat\n");
}


void printfMenu(){



}


int printfEditReaderInf(){ // return max choices
	printf("Sua ten doc gia\n");
	printf("Sua CMND\n");
	printf("Sua ngay thang nam sinh\n");
	printf("Doi gioi tinh\n" );
	printf("Sua dia chi email\n");
	printf("Sua dia chi sinh song\n");
	printf("Dieu chinh ngay het han the\n");

	return 7;
}