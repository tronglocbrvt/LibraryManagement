#include "LibraryManagement.h"
#include "commonFunction.h"
#include "Menu.h"
#include "userManagement.h"
#include "readerManagement.h"
#include "bookManagement.h"
#include "borrowedBooks.h"
#include "linkedListBorrowBook.h"
#include "returnedBooks.h"
#include "analyzingLibrary.h"


#if defined(_WIN64) || defined(_WIN32)
	void stopSceen(){
		textBgColor(YELLOW, BLACK);
		printf("Nhan phim bat ky de quay lai...");
		getch();
	}
#else 
	void flushall(){

	}
	void Sleep(int time){
		cout << "Enter to continue the program";
		cin.ignore().get(); //Pause Command for Linux Terminal
	}
	void stopSceen(){
		cout << "Enter to continue the program";
		cin.ignore().get(); //Pause Command for Linux Terminal
	}
#endif

int main()
{
	do
	{
		system(cls);
		int typeAccount;
		resizeConsole(1200, 1200);
		do
		{
			system(cls);
			typeAccount = Login(); // Đăng nhập, trả về 0 nếu thất bại, trả về 1 nếu là admin, trả về 2 là chuyên viên, trả về 3 là quản lý
			if (typeAccount == 0)
			{
				textBgColor(RED, BLACK);
				printf("Dang nhap that bai. Vui long thu lai!\n");
				// getch();
				Sleep(1000);
			}
			else if (typeAccount == -1)
			{
				textBgColor(RED, BLACK);
				printf("Xin loi! Tai khoan cua ban dang o trang thai Blocked.\n");
				// getch();
				Sleep(1000);
			}
		} while (typeAccount == 0 || typeAccount == -1);
		textBgColor(RED, BLACK);
		printf("Dang nhap thanh cong!\n");
		textBgColor(WHITE, BLACK);

		Sleep(1000);
		bool continueSwit = true;
		while (continueSwit){
			int choice = printLoginMenu();
			switch (choice){
			case 0:
				continueSwit = false;
				typeAccount = Logout();
				return 0;
			case 1:
				runMenuUser(typeAccount);
				break;
			case 2:
				runReaderManagement(typeAccount);
				break;
			case 3:
				runBookManagement(typeAccount);
				break;
			case 4:
				borrowBook();
				break;
			case 5:
				returnBook();
				break;
			case 6:
				runningAnalyzing(typeAccount);
				break;
			case 7:
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
