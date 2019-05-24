#include "LibraryManagement.h"
#include "Menu.h"
#include "commonFunction.h"
#include "userManagement.h"

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

	int main(int argc, char *agrv[])
	{
		if (argc == 2)
		{
			if (strcmpi(agrv[1], "login") == 0)
			{
				textBgColor(WHITE, BLACK);
				system("cls");
				resizeConsole(707, 707);
				int typeAccount = Login();
				if (typeAccount == 0)
				{
					textBgColor(RED, BLACK);
					printf("Dang nhap that bai. Vui long thu lai!\n");
					textBgColor(WHITE, BLACK);
					Sleep(1000);
					system("cls");
				}
				else if (typeAccount == -1)
				{
					textBgColor(RED, BLACK);
					printf("Xin loi! Tai khoan cua ban dang o trang thai Blocked.\n");
					textBgColor(WHITE, BLACK);
					Sleep(1000);
					system("cls");
				}
				else
				{
					textBgColor(RED, BLACK);
					printf("Dang nhap thanh cong!\n");
					textBgColor(WHITE, BLACK);
					Sleep(1000);
					Menu(typeAccount);
				}
			}
			else
			{
				textBgColor(RED, BLACK);
				printf("Vui long nhap dung cu phap (LibraryManagement.exe login)\n");
				textBgColor(WHITE, BLACK);
				Sleep(1000);
			}
		}
		else
		{
			textBgColor(RED, BLACK);
			printf("Vui long nhap dung cu phap (LibraryManagement.exe login)\n");
			textBgColor(WHITE, BLACK);
			Sleep(1000);
		}
		return 0;
	}
	