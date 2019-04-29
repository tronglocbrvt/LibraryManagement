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
			return false;
		}
	}

	fclose(f);

	return true;
}

// Hàm nhập Username
void getUsername(Users &A)
{
	do
	{
		printf("Nhap Username (toi da 20 ky tu): ");
		scanf("%s", &A.Username);
		int temp = getchar();
		if (!checkUsername(A.Username))
			printf("Username da ton tai. Vui long nhap Username khac.\n");
	} while (!checkUsername(A.Username));
}

// Hàm nhập Ngày sinh
void getBirthday(Users &A)
{
	bool checkDay;
	do
	{
		printf("Nhap ngay sinh: ");
		scanf("%d", &A.Birthday.Date);
		int temp = getchar();

		printf("Nhap thang sinh: ");
		scanf("%d", &A.Birthday.Month);
		temp = getchar();

		printf("Nhap nam sinh: ");
		scanf("%d", &A.Birthday.Year);
		temp = getchar();

		checkDay = isPossibleDay(A.Birthday.Date, A.Birthday.Month, A.Birthday.Year);
		if (!checkDay)
			printf("Ngay thang nam sinh khong hop le vui long nhap lai.\n");
	} while (checkDay == false);
}

// Hàm nhập CMND
void getNationalID(Users &A)
{
	int flag = 0;
	do
	{
		printf("Nhap CMND (9 so hoac 12 so): ");
		scanf("%s", &A.NationID);
		int temp = getchar();
		int i;
		if (strlen(A.NationID) != 9 && strlen(A.NationID) != 12)
		{
			printf("CMND khong hop le. Vui long nhap lai.\n");
			continue;
		}

		flag = 1; 

		for (int i = 0; i < strlen(A.NationID); i++)
		{
			if (!isNumber(A.NationID[i]))
			{
				flag = 0;
				printf("CMND khong hop le. Vui long nhap lai.\n");
				break;
			}
		}
	} while (flag == 0);

}

// Hàm nhập giới tính
void getSex(Users &A)
{
	do
	{
		printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
		scanf("%d", &A.Sex);
		int temp = getchar();

		if (A.Sex != 0 && A.Sex != 1)
			printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
	} while (A.Sex != 0 && A.Sex != 1);
}

// Hàm nhập tình trạng
void getStatus(Users &A)
{
	do
	{
		printf("Nhap tinh trang (Actived nhap 1; Blocked nhap 0): ");
		scanf("%d", &A.Status);
		int temp = getchar();

		if (A.Status != 0 && A.Status != 1)
			printf("Vui long nhap lai. Actived nhap 1, Blocked nhap 0.\n");
	} while (A.Status != 0 && A.Status != 1);
}

// Hàm nhập phân quyền
void getTypeAccount(Users &A)
{
	do
	{
		printf("Nhap phan quyen (Chuyen vien nhap 2; quan ly nhap 3): ");
		scanf("%d", &A.typeAccount);
		int temp = getchar();

		if (A.typeAccount != 2 && A.typeAccount != 3)
			printf("Vui long nhap lai. Chuyen vien nhap 2; quan ly nhap 3.\n");
	} while (A.typeAccount != 2 && A.typeAccount != 3);
}

// Nhập thông tin người dùng
Users addUser()
{
	Users A;
	int temp;

	getUsername(A);

	printf("Nhap Password (toi da 16 ky tu): ");
	scanf("%s", &A.Password);
	temp = getchar();

	printf("Nhap Ho va Ten: ");
	gets(A.Fullname);

	getBirthday(A);

	getNationalID(A);

	printf("Nhap dia chi: ");
	gets(A.Address);

	getSex(A);

	getStatus(A);

	getTypeAccount(A);

	return A;
}

// Ghi vào file thông tin người dùng
void writeFile()
{
	Users A = addUser();

	FILE *f = fopen("Release/Users/Users.bin", "ab");

	if (f == NULL)
		return;

	fwrite(&A, sizeof(Users), 1, f);
	fclose(f);

	fprintf(f, A.Username);

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
		writeFile();
		printf("Tao nguoi dung thanh cong!\n");
	}
	else
	{
		printf("Xin loi! Quyen nay chi danh cho Admin.\n");
	}
}