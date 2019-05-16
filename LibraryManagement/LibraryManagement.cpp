﻿#include "LibraryManagement.h"
#include "commonFunction.h"
#include "createUser.h"
#include "Login_Logout.h"
#include "Menu.h"
#include "changePassword.h"
#include "changeProfile.h"
#include "decentraliseUsers.h"
#include "statusUser.h"
#include "runUser.h"
#include "readerManagement.h"
#include "bookManagement.h"
#include "borrowedBooks.h"

#if defined(_WIN64) || defined(_WIN32)
	#define cls "cls"
	#include <tchar.h>
	#include <conio.h>
	#include <windows.h>
	// void clearSTDIN(){
	// 	flushall();
	// }
#else 
	#define cls "clear"
	#include "conioLinux.h"
	// void clearSTDIN(){
	// 	tcflush(0, TCIFLUSH);
	// }
	void flushall(){

	}
	void Sleep(int time){
		cout << "Enter to continue the program";
		cin.ignore().get(); //Pause Command for Linux Terminal
	}
#endif

int main()
{
	do
	{
		int typeAccount;
		resizeConsole(1500, 1500);
		do
		{
			system(cls);
			typeAccount = Login(); // Đăng nhập, trả về 0 nếu thất bại, trả về 1 nếu là admin, trả về 2 là chuyên viên, trả về 3 là quản lý
			if (typeAccount == 0)
			{
				textBgColor(RED, BLACK);
				printf("Dang nhap that bai. Vui long nhan phim bat ky thu lai!\n");
				// getch();
				cout << "Enter to exit the program";
				cin.ignore().get(); //Pause Command for Linux Terminal
			}
			else if (typeAccount == -1)
			{
				textBgColor(RED, BLACK);
				printf("Xin loi! Tai khoan cua ban dang o trang thai Blocked.\n");
				// getch();
				cout << "Enter to exit the program";
				cin.ignore().get(); //Pause Command for Linux Terminal
			}
		} while (typeAccount == 0 || typeAccount == -1);

		textBgColor(RED, BLACK);
		printf("Dang nhap thanh cong!\n");
		textBgColor(WHITE, BLACK);

<<<<<<< HEAD
		runBookManagement();
		borrowBook();
=======
>>>>>>> 982b91d5e8e54275cfd7950cb6571fd2c0dd1b13

		system("pause");
		bool continueSwit = true;
		while (continueSwit){
			//printfMenu(); // ke vien khung ung dung
			int choice = printLoginMenu();
			switch (choice){ // add function doing here
			case 0:
				continueSwit = false;
				typeAccount = Logout();
				exit(0);
			case 1:
				runMenuUser(typeAccount);
				break;
			case 2:
				runReaderManagement();
				break;
			case 3:
				runBookManagement();
				break;
			case 4:
				printf("pheiumuonsach\n");
				break;
			case 5:
				printf("phieutrasach\n");
				break;
			case 6:
				printf("thongke\n");
				break;
			case 7:
				printf("Dang xuat\n");
				continueSwit = false;
				typeAccount = Logout();
				break;
			default:
				break;
			}
		}
	} while (true);

	return 0;
}
// now now
