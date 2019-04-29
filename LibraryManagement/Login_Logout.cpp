#include "Login_Logout.h"
#include "Menu.h"
/* Hàm đăng nhập, nếu đăng nhập thành công thì trả về
	1: Admin
	2: Chuyên viên
	3: Quản lý
   Hàm đăng nhập thất bại trả về 0
*/
int checkLogin(char *Username, char *Password)
{
	// Kiểm tra Username và Password trong file Admin không?
	Users A;

	FILE *fCur = fopen("Release/Current/currentUser.bin", "wb");

	FILE *f = fopen("Release/Users/Users.bin", "rb");

	if (f == NULL || fCur == NULL)
		return 0;

	while (fread(&A, sizeof(Users), 1, f) != NULL)
	{

		if ((strcmp(A.Username, Username) == 0) && (strcmp(A.Password, Password) == 0))
		{
			if (A.Status == 1)
			{
				fwrite(&A, sizeof(Users), 1, fCur);
				fclose(fCur);
				fclose(f);
				return A.typeAccount;
			}
			else
			{
				return -1;
			}
		}
	}
	return 0;
}

// Hàm đăng xuất
int Logout()
{
	remove((char*)"Release/Current/currentUser.bin");
	return -1;
}

//Hàm đăng nhập
int Login()
{
	gotoxy(30,0);
	printf("Moi ban dang nhap: \n\n");
	printf("Nhap ten tai khoan: ");
	char *username = new char[21];
	scanf("%s", username);
	
	printf("Nhap mat khau: ");
	char *password = new char[17];
	scanf("%s", password);

	int typeAccount = checkLogin(username, password);

	delete[] username;
	delete[] password;

	return typeAccount;
}