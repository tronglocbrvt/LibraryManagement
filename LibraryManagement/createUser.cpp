#include "createUser.h"
#include "commonFunction.h"

// Kiểm tra Username tồn tại chưa?
bool checkUsername(char *Username)
{
	// Kiểm tra Username trùng với admin hay không?

	if (strcmp(Username, "admin") == 0)
		return false;

	Users A;
	FILE *f = fopen("Release/Users/Users.bin", "rb");

	if (f == NULL)
		return 0;

	while (fread(&A,sizeof(Users), 1, f) != NULL)
	{
		if (strcmp(A.Username, Username) == 0)
		{
			fclose(f);
			return false;
		}
	}

	fclose(f);

	return true;
}

// Nhập thông tin người dùng
Users addUser()
{
	Users A;

	flushall();
	getUsername(A.Username);

	printf("Nhap Password (toi da 16 ky tu): ");
	scanf("%s", &A.Password);
	flushall();

	printf("Nhap Ho va Ten: ");
	gets(A.Fullname);

	getBirthday(A.Birthday);

	getNationalID(A.NationID);

	printf("Nhap dia chi: ");
	gets(A.Address);

	getSex(A.Sex);

	getStatus(A.Status);

	getTypeAccount(A);
	
	return A;
}

// Ghi vào file thông tin người dùng
void writeInfUsertoFile()
{
	Users A = addUser();

	FILE *f = fopen("Release/Users/Users.bin", "ab");

	if (f == NULL)
		return;

	fwrite(&A, sizeof(Users), 1, f);
	fclose(f);
}

// Tạo người dùng
void getUser(int typeAccount)
{
	/* Kiểm tra xem tài khoản đăng nhập hiện tại có phải là admin hay không?
	   Nếu là admin thì thực hiện chức năng.
	   Ngược lại không được tạo tài khoản (vì tạo tài khoản duy nhất là quyền của admin.) */
	if (typeAccount == 1) 
	{
		writeInfUsertoFile();
		printf("Tao nguoi dung thanh cong!\n");
	}
	else
	{
		printf("Xin loi! Quyen nay chi danh cho Admin.\n");
	}
}