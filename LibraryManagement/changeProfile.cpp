﻿#include "changeProfile.h"
#include "commonFunction.h"
#include "createUser.h"
#include "changePassword.h"

// Hàm xem thông tin cá nhân
void viewProfile()
{
	Users curUser;

	FILE *fCur = fopen("Release/Current/currentUser.bin", "rb");

	if (fCur == NULL)
		return;

	fread(&curUser, sizeof(Users), 1, fCur);

	printf("--------------------------------------------------------\n");
	printf("Thong tin ca nhan cua Username %s:\n\n", curUser.Username);
	printf("Ho va ten: %s\n", curUser.Fullname);
	printf("Ngay sinh: %d/%d/%d\n", curUser.Birthday.Date, curUser.Birthday.Month, curUser.Birthday.Year);
	printf("CMND: %s\n", curUser.NationID);
	printf("Dia chi: %s\n", curUser.Address);
	printf("Gioi tinh (nam la 1, nu la 0): %d\n", curUser.Sex);
	printf("--------------------------------------------------------\n");

	fclose(fCur);
}

// Hàm hỏi người dùng muốn chỉnh sửa nữa không?
int wantEdit()
{
	int edit = 0;
	printf("Ban con muon chinh sua nua khong? Nhap 0 (Khong), Nhap 1 (Co): ");
	do
	{
		scanf("%d", &edit);
		if (edit == 1)
			return 1;
		else if (edit == 0)
			return 0;
		else
			printf("Vui long nhap 0 hoac 1\n");
	} while (edit != 0 && edit != 1);
	return edit;
}

// Hàm chỉnh sửa thông tin cá nhân
void editProfile()
{
	viewProfile();

	Users curUser;
	int choice;
	int temp;

	FILE *fCur = fopen("Release/Current/currentUser.bin", "rb");

	if (fCur == NULL)
		return;

	fread(&curUser, sizeof(Users), 1, fCur);

	bool end = false;
	int edit;

	do
	{
	printf("Nhap so de chinh sua thong tin tuong ung: \n");
	printf("1. Ho va ten \t 2. Ngay sinh \t 3. CMND \t 4. Dia chi \t 5. Gioi tinh\n");
	scanf("%d", &choice);
	
		switch (choice)
		{
		case 1:
			printf("Nhap ho va ten moi: ");
			temp = getchar();
			gets(curUser.Fullname);

			edit = wantEdit();
			if (edit == 0)
				end = true;
			temp = getchar();
			break;
		case 2:
			printf("Nhap lai ngay sinh moi:\n");
			getBirthday(curUser);

			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 3:
			getNationalID(curUser);

			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 4: 
			printf("Nhap lai dia chi moi: ");
			temp = getchar();
			gets(curUser.Address);

			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 5: 
			getSex(curUser);

			edit = wantEdit();
			if (edit == 0)
				end = true;
			temp = getchar();
			break;
		default:
			printf("Vui long nhap tu 1 den 5.\n");
			break;
		}
	} while (end == false);

	fclose(fCur);

	FILE *fw = fopen("Release/Current/currentUser.bin", "wb"); // cập nhật lại thông tin trong file currentUser

	if (fw == NULL)
		return;

	fwrite(&curUser, sizeof(Users), 1, fw);
	fclose(fw);

	updateFile(curUser);

	viewProfile();
}
