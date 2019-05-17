#include "Menu.h"
#include "commonFunction.h"

//=================================================
// on window
#if defined(_WIN32) || defined(_WIN64)
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
#else
	 void resizeConsole(int width, int height)
	 {
	 	
	 }
	 void gotoxy(int x, int y)
	 {
	     
	 }
#endif
 
//=================================================



int printLoginMenu(){
	 printf("*******************************************\n");
	 gotoxy(10,1);

	// do somthing here: check if username is exist and password is right
	bool checkUsername = 1;
	bool checkPassword = 1;

	if (checkUsername && checkPassword)
	{
		system(cls);
		printfMainMenu();
		return getNumberPressKey(MAX_CHOICE, 0);
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


int printUserMenu(int typeAccount)
{
	system(cls);
	printf("1. Thay doi mat khau.\n");
	printf("2. Cap nhat thong tin ca nhan.\n");

	if (typeAccount == 1)
	{
		printf("3. Tao nguoi dung.\n");
		printf("4. Phan quyen nguoi dung.\n");
		printf("5. Chinh sua trang thai nguoi dung.\n");
	}

	printf("0. Quay ve.\n");
	
	if (typeAccount == 1)
		return 5;
	
	return 2;
}


int printfMenuReaderManagement(){
	system(cls);
	printf("1. Xem danh sach doc gia trong thu vien.\n");
	printf("2. Them doc gia.\n");
	printf("3. Chinh sua thong tin mot doc gia.\n");
	printf("4. Xoa thong tin mot doc gia.\n");
	printf("5. Tim kiem doc gia qua CMND.\n");
	printf("6. Tim kiem doc gia qua ho ten.\n");
	printf("0. Quay ve\n");

	return 6;
}

int printfMenuBookManagement(){
	system(cls);
	printf("1. Xem danh sach sach trong thu vien.\n");
	printf("2. Them sach.\n");
	printf("3. Chinh sua thong tin mot quyen sach.\n");
	printf("4. Xoa thong tin mot quyen sach.\n");
	printf("5. Tim kiem sach qua ISBN.\n");
	printf("6. Tim kiem sach qua ten sach.\n");
	printf("0. Quay ve\n");

	return 6;
}

int editInfReaderMenu(){
	system(cls);
	printf("1. Sua Ho va ten\n");
	printf("2. Doi CMND\n");
	printf("3. Doi ngay sinh\n");
	printf("4. Doi gioi tinh\n");
	printf("5. Doi Email\n");
	printf("6. Doi dia chi\n");
	printf("7. Gia han the\n");
	printf("0. Quay ve\n");

	return 7;
}

int editInfBookMenu(){
	system(cls);
	printf("1. Sua ten sach\n");
	printf("2. Sua ten tac gia\n");
	printf("3. Sua ten nha xuat ban\n");
	printf("4. Sua nam xuat ban\n");
	printf("5. Sua the loai sach\n");
	printf("6. Sua gia sach\n");
	printf("7. Sua so luong sach\n");
	printf("0. Quay ve\n");

	return 7;
}