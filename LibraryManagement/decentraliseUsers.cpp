#include "decentraliseUsers.h"
#include "createUser.h"
#include "changePassword.h"

void inforUser()
{
	Users A;

	FILE *f = fopen("Release/Users/Users.bin", "rb");

	while (fread(&A, sizeof(Users), 1, f) != NULL)
	{
		if (A.typeAccount == 2)
			printf("%s\t\t%s\n", A.Username, "Chuyen vien");
		else if (A.typeAccount == 3)
			printf("%s\t\t%s\n", A.Username, "Quan li");
	}

	fclose(f);
}

void decentraliseUser(int typeAccount)
{
	if (typeAccount != 1)
	{
		printf("Xin loi! Quyen nay chi danh cho Admin.\n");
		return;
	}

	inforUser();

	char *Username = new char[21];
	int flag; 

	do
	{
		int temp = getchar();
		printf("Nhap Username ban muon phan quyen: ");
		scanf("%s", Username);

		flag = checkUsername(Username); // flag = 0: tìm thấy Username; flag = 1: không tìm thấy Username.
		if (flag == 1)
			printf("Khong tim thay Username ban da nhap. Vui long thu lai.\n");
		if (strcmp(Username, "admin") == 0)
			printf("Ban khong the phan quyen cho admin.\n");
	} while (strcmp(Username, "admin") == 0 || flag == 1);

	Users A;
	FILE *f = fopen("Release/Users/Users.bin", "rb");
	while (fread(&A, sizeof(Users), 1, f) != NULL)
	{
		if (strcmp(A.Username, Username) == 0)
		{
			getTypeAccount(A);
			break;
		}
	}

	fclose(f);

	updateFile(A);

	printf("Ban da phan quyen thanh cong!\n");

	inforUser();
	
	delete[] Username;
}