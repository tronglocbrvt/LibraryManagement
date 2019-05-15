#include "LibraryManagement.h"
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

int main()
{
	do
	{
		int typeAccount;
		resizeConsole(700, 700);
		do
		{
			system("cls");
			typeAccount = Login(); // Đăng nhập, trả về 0 nếu thất bại, trả về 1 nếu là admin, trả về 2 là chuyên viên, trả về 3 là quản lý
			if (typeAccount == 0)
			{
				textBgColor(RED, BLACK);
				printf("Dang nhap that bai. Vui long nhan phim bat ky thu lai!\n");
				getch();
			}
			else if (typeAccount == -1)
			{
				textBgColor(RED, BLACK);
				printf("Xin loi! Tai khoan cua ban dang o trang thai Blocked.\n");
				getch();
			}
		} while (typeAccount == 0 || typeAccount == -1);

		textBgColor(RED, BLACK);
		printf("Dang nhap thanh cong!\n");
		textBgColor(WHITE, BLACK);

		runBookManagement();

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
				printf("nguoidoc\n");
				break;
			case 3:
				printf("sach\n");
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
