#include "changePassword.h"

// Hàm Update file
void updateFile(Users curUser)
{

	FILE *fo = fopen(_DIR_DATA_FOLDER_USER, "rb");
	FILE *ftemp = fopen(_DIR_DATA_FOLDER_USER_TEMP, "wb");

	if (fo == NULL || ftemp == NULL)
		return;

	Users temp;

	while (fread(&temp, sizeof(Users), 1, fo) != 0)
	{
		if (strcmp(curUser.Username, temp.Username) != 0)
			fwrite(&temp, sizeof(Users), 1, ftemp);
		else
			fwrite(&curUser, sizeof(Users), 1, ftemp);
	}


	fclose(fo);
	fclose(ftemp);
	remove((char*)_DIR_DATA_FOLDER_USER);
	rename((char*)_DIR_DATA_FOLDER_USER_TEMP, (char*)_DIR_DATA_FOLDER_USER);

}

// Hàm đổi mật khẩu
void ChangePassword()
{
	Users curUser;
	char *oldPassword = new char[16];
	char *newPassword1 = new char[16];
	char *newPassword2 = new char[16];

	FILE *f = fopen(_DIR_DATA_FOLDER_USER_CUR, "rb"); // mở File chứa thông tin tài khoản đang đăng nhập

	if (f == NULL)
		return; 

	fread(&curUser, sizeof(Users), 1, f);
	do
	{
		printf("Moi ban nhap mat khau cu: ");
		scanf("%s", oldPassword);

		printf("Moi ban nhap mat khau moi: ");
		scanf("%s", newPassword1);

		printf("Moi ban xac nhan mat khau moi: ");
		scanf("%s", newPassword2);

		if (strcmp(oldPassword, curUser.Password) != 0) // Mật khẩu không khớp với mật khẩu đã tạo
		{
			printf("Ban da nhap sai mat khau cu.\n");
		}

		if (strcmp(newPassword1, newPassword2) != 0) // Mật khẩu xác nhận không khớp với mật khẩu vừa nhập
		{
			printf("Mat khau xac nhan khong khop.\n");
		}

	} while (strcmp(oldPassword, curUser.Password) != 0 || strcmp(newPassword1, newPassword2) != 0);

	strcpy(curUser.Password, newPassword1);
	fclose(f);

	FILE *fw = fopen(_DIR_DATA_FOLDER_USER_CUR, "wb");

	if (fw == NULL)
		return;

	fwrite(&curUser, sizeof(Users), 1, fw);
	fclose(fw);

	updateFile(curUser);

	printf("Ban da doi mat khau thanh cong!\n");

	delete[] oldPassword;
	delete[] newPassword1;
	delete[] newPassword2;

}