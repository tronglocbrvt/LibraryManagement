#include "statusUser.h"
#include "createUser.h"
#include "changePassword.h"
#include "commonFunction.h"

void inforStatusUser()
{
	Users A;

	FILE *f = fopen("Release/Users/Users.bin", "rb");
	
	if (f == NULL)
		return;

	while (fread(&A, sizeof(Users), 1, f) != NULL)
	{
		if (A.Status == 0)
			printf("%s\t\t%s\n", A.Username, "Blocked");
		else if (A.Status == 1)
			printf("%s\t\t%s\n", A.Username, "Actived");
	}

	fclose(f);
}

void changeStatusUser(int typeAccount)
{
	if (typeAccount != 1)
	{
		printf("Xin loi! Quyen nay chi danh cho Admin.\n");
		return;
	}

	inforStatusUser();

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
	
	if (f == NULL)
		return;

	while (fread(&A, sizeof(Users), 1, f) != NULL)
	{
		if (strcmp(A.Username, Username) == 0)
		{
			getStatus(A.Status);
			break;
		}
	}

	fclose(f);

	updateFile(A);

	printf("Ban da cap nhat trang thai thanh cong!\n");

	inforStatusUser();

	delete[] Username;
}