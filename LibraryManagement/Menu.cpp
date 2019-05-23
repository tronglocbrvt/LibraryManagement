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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

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
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void printfMainMenu(){
	textBgColor(BLUE, LIGHTAQUA);
	showTitleHeader();
	textBgColor(WHITE, BLACK);
	gotoxy(25, 6);
	printf("1. Quan ly nguoi dung.\n");
	gotoxy(25, 7);
	printf("2. Quan ly doc gia.\n");
	gotoxy(25, 8);
	printf("3. Quan ly sach.\n");
	gotoxy(25, 9);
	printf("4. Lap phieu muon sach.\n");
	gotoxy(25, 10);
	printf("5. Lap phieu tra sach.\n");
	gotoxy(25, 11);
	printf("6. Thong ke co ban.\n");
	gotoxy(25, 12);
	printf("7. Dang xuat.\n");
	gotoxy(25, 13);
	printf("0. Thoat\n");

}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void showTitleUser(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                          >> QUAN LY NGUOI DUNG <<                              ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}

int printUserMenu(int typeAccount)
{
	system(cls);
	showTitleUser();
	gotoxy(25, 6);
	printf("1. Thay doi mat khau.\n");
	gotoxy(25, 7);
	printf("2. Cap nhat thong tin ca nhan.\n");

	if (typeAccount == 1)
	{
		gotoxy(25, 8);
		printf("3. Tao nguoi dung.\n");
		gotoxy(25, 9);
		printf("4. Phan quyen nguoi dung.\n");
		gotoxy(25, 10);
		printf("5. Chinh sua trang thai nguoi dung.\n");
		gotoxy(25, 11);
		printf("0. Quay ve.\n");
		return 5;
	}
	else
	{
		gotoxy(25, 8);
		printf("0. Quay ve.\n");
		return 2;
	}
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//void drawRectangle(int positionX, int positionY, int width, int height, int color)
//{
//	textBgColor(0, color);
//	gotoxy(positionX, positionY);
//	for (int y = 0; y < height; y++)
//	{
//		for (int x = 0; x < width; x++)
//		{
//			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
//			{
//				gotoxy(positionX + x, positionY + y);
//				printf("%c", '*');
//			}
//		}
//	}
//}
void showTitleReader(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                            >> QUAN LY DOC GIA <<                               ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}

int printfMenuReaderManagementForAdmin(){
	system(cls);
	//drawRectangle(30, 16, 30, 4, BLUE);
	showTitleReader();
	gotoxy(25, 6);
	printf("1. Xem danh sach doc gia trong thu vien.\n");
	gotoxy(25, 7);
	printf("2. Them doc gia.\n");
	gotoxy(25, 8);
	printf("3. Chinh sua thong tin mot doc gia.\n");
	gotoxy(25, 9);
	printf("4. Xoa thong tin mot doc gia.\n");
	gotoxy(25, 10);
	printf("5. Tim kiem doc gia qua CMND.\n");
	gotoxy(25, 11);
	printf("6. Tim kiem doc gia qua ho ten.\n");
	gotoxy(25, 12);
	printf("0. Quay ve\n");

	return 6;
}

int printfMenuReaderManagementForExpert(){
	system(cls);
	showTitleReader();
	gotoxy(25, 6);
	printf("1. Xem danh sach doc gia trong thu vien.\n");
	gotoxy(25, 7);
	printf("2. Them doc gia.\n");
	gotoxy(25, 8);
	printf("3. Chinh sua thong tin mot doc gia.\n");
	gotoxy(25, 9);
	printf("4. Tim kiem doc gia qua CMND.\n");
	gotoxy(25, 10);
	printf("5. Tim kiem doc gia qua ho ten.\n");
	gotoxy(25, 11);
	printf("0. Quay ve\n");

	return 5;
}

int printfMenuReaderManagementForManager(){
	system(cls);
	showTitleReader();
	gotoxy(25, 6);
	printf("1. Xem danh sach doc gia trong thu vien.\n");
	gotoxy(25, 7);
	printf("2. Them doc gia.\n");
	gotoxy(25, 8);
	printf("3. Chinh sua thong tin mot doc gia.\n");
	gotoxy(25, 9);
	printf("4. Xoa thong tin mot doc gia.\n");
	gotoxy(25, 10);
	printf("5. Tim kiem doc gia qua CMND.\n");
	gotoxy(25, 11);
	printf("6. Tim kiem doc gia qua ho ten.\n");
	gotoxy(25, 12);
	printf("0. Quay ve\n");

	return 6;
}

int editInfReaderMenu(){
	textBgColor(WHITE, BLACK);
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
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void showTitleBook(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                             >> QUAN LY SACH <<                                 ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}

int printfMenuBookManagementForAdmin(){
	system(cls);
	showTitleBook();
	gotoxy(25, 6);
	printf("1. Xem danh sach sach trong thu vien.\n");
	gotoxy(25, 7);
	printf("2. Them sach.\n");
	gotoxy(25, 8);
	printf("3. Chinh sua thong tin mot quyen sach.\n");
	gotoxy(25, 9);
	printf("4. Xoa thong tin mot quyen sach.\n");
	gotoxy(25, 10);
	printf("5. Tim kiem sach qua ISBN.\n");
	gotoxy(25, 11);
	printf("6. Tim kiem sach qua ten sach.\n");
	gotoxy(25, 12);
	printf("0. Quay ve\n");

	return 6;
}

int printfMenuBookManagementForExpert(){
	system(cls);
	showTitleBook();
	gotoxy(25, 6);
	printf("1. Tim kiem sach qua ISBN.\n");
	gotoxy(25, 7);
	printf("2. Tim kiem sach qua ten sach.\n");
	gotoxy(25, 8);
	printf("0. Quay ve\n");

	return 2;
}

int printfMenuBookManagementForManager(){
	system(cls);
	showTitleBook();
	gotoxy(25, 6);
	printf("1. Xem danh sach sach trong thu vien.\n");
	gotoxy(25, 7);
	printf("2. Them sach.\n");
	gotoxy(25, 8);
	printf("3. Chinh sua thong tin mot quyen sach.\n");
	gotoxy(25, 9);
	printf("4. Xoa thong tin mot quyen sach.\n");
	gotoxy(25, 10);
	printf("5. Tim kiem sach qua ISBN.\n");
	gotoxy(25, 11);
	printf("6. Tim kiem sach qua ten sach.\n");
	gotoxy(25, 12);
	printf("0. Quay ve\n");

	return 6;
}

int editInfBookMenu(){
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
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int askYesNoQuestion(char *note){
	printf("%s?\n", note);
	printf("1. Co\n");
	printf("2. Khong\n");

	return 2;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void showTitleAnalyzing(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                                >> THONG KE <<                                  ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);	
}

int analyzingMenuForAdmin(){
	system(cls);
	showTitleAnalyzing();
	gotoxy(25, 6);
	printf("1. Thong ke so luong sach trong thu vien.\n");
	gotoxy(25, 7);
	printf("2. Thong ke so luong sach theo the loai.\n");
	gotoxy(25, 8);
	printf("3. Thong ke so luong doc gia.\n");
	gotoxy(25, 9);
	printf("4. Thong ke so luong doc gia theo gioi tinh.\n");
	gotoxy(25, 10);
	printf("5. Thong ke so luong sach dang duoc muon.\n");
	gotoxy(25, 11);
	printf("6. Thong ke danh sach doc gia bi tre han.\n");
	gotoxy(25, 12);
	printf("0. Quay ve.\n");

	return 6;
}

int analyzingMenuForExpert(){
	system(cls);
	showTitleAnalyzing();
	gotoxy(25, 6);
	printf("1. Thong ke so luong sach dang duoc muon.\n");
	gotoxy(25, 7);
	printf("2. Thong ke danh sach doc gia bi tre han.\n");
	gotoxy(25, 8);
	printf("0. Quay ve.\n");

	return 2;
}

int analyzingMenuManager(){
	system(cls);
	showTitleAnalyzing();
	gotoxy(25, 6);
	printf("1. Thong ke so luong sach trong thu vien.\n");
	gotoxy(25, 7);
	printf("2. Thong ke so luong sach theo the loai.\n");
	gotoxy(25, 8);
	printf("3. Thong ke so luong doc gia.\n");
	gotoxy(25, 9);
	printf("4. Thong ke so luong doc gia theo gioi tinh.\n");
	gotoxy(25, 10);
	printf("0. Quay ve.\n");

	return 4;
}

void showTitleHeader(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                           >> QUAN LY THU VIEN <<                               ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);	
}

void showFooter(){
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
}

void showTitleBorrow(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                          >> LAP PHIEU MUON SACH <<                             ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);	
}

void showTitleReturn(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                           >> LAP PHIEU TRA SACH <<                             ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);	
}
//>>>>>>>>>>>>>>>>>>>>>>>>. sub meunu title
void showTitleOverdue(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                    >> DANH SACH TRE HAN TRA SACH <<                            ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);	
}
void showTitleListBook(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                  >> DANH SACH SACH TRONG THU VIEN <<                           ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);	
}
void showTitleCategory(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                        >> DANH SACH THE LOAI <<                                ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);	
}
void showTitleListReader(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                         >> DANH SACH DOC GIA <<                                ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);	
}
void showTitleMaleReader(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                  >> DANH SACH DOC GIA THEO GIOI TINH <<                        ||\n");
	printf("|----------------------------------NAM---------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);	
}
void showTitleFemaleReader(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                  >> DANH SACH DOC GIA THEO GIOI TINH <<                        ||\n");
	printf("|-----------------------------------NU---------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);	
}
void showTitleListBorrowing(){
	textBgColor(BLUE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                   >> DANH SACH CAC SACH DA DUOC MUON <<                        ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);	
}

//>>>>>>>>>>>>>>>>>>>>>>>> title chức năng reader
void showTitleViewReader(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                          >> XEM THONG TIN DOC GIA <<                           ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleAddNewReader(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                              >> THEM DOC GIA <<                                ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleEditReader(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                       >> CHINH SUA THONG TIN DOC GIA <<                        ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleAfterEditReader(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                     >> THONG TIN DOC GIA SAU CHINH SUA <<                      ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleDeleteReader(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                               >> XOA DOC GIA <<                                ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleFindReaderByNationId(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                        >> TIM KIEM DOC GIA QUA CMND <<                         ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleFindReaderByName(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                       >> TIM KIEM DOC GIA QUA HO TEN <<                        ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
//>>>>>>>>>>>>>>>>>>>>>>>> title chức năng user
void showTitleCreatUser(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                            >> TAO NGUOI DUNG <<                                ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleDecentraliseUser(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                         >> PHAN QUYEN NGUOI DUNG <<                            ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	
	textBgColor(BLUE, BLACK);
}
void showTitleChangePassUser(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                          >> THAY DOI MAT KHAU <<                               ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");

	textBgColor(WHITE, BLACK);
}
void showTitleStatusUser(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                     >> CHINH SUA TRANG THAI NGUOI DUNG <<                      ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");

	textBgColor(BLUE, BLACK);
}
void showTitleAfterEditUser(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                       >> CAP NHAT THONG TIN CA NHAN <<                         ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(PURPLE, BLACK);
}


//>>>>>>>>>>>>>>>>>>>>>>>> title chức năng book
void showTitleViewBook(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                           >> XEM THONG TIN SACH <<                             ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleAddNewBook(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                                >> THEM SACH <<                                 ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleEditBook(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                         >> CHINH SUA THONG TIN SACH <<                         ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleAfterEditBook(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                       >> THONG TIN SACH SAU CHINH SUA <<                       ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleDeleteBook(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                                 >> XOA SACH <<                                 ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleFindBookByISBN(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                          >> TIM KIEM SACH QUA CMND <<                          ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}
void showTitleFindBookByName(){
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                        >> TIM KIEM SACH QUA TEN SACH <<                        ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
}