#include "userManagement.h"
#include "commonFunction.h"
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

	FILE *fCur = fopen(_DIR_DATA_FOLDER_USER_CUR, "wb");

	FILE *f = fopen(_DIR_DATA_FOLDER_USER, "rb");

	if (f == NULL || fCur == NULL)
		return 0;

	while (fread(&A, sizeof(Users), 1, f) != 0)
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
				fclose(fCur);
				fclose(f);
				return -1;
			}
		}
	}
	fclose(fCur);
	fclose(f);
	return 0;
}

// Hàm đăng xuất
int Logout()
{
	remove((char*)_DIR_DATA_FOLDER_USER_CUR);
	return -1;
}

//Hàm đăng nhập
int Login()
{
	gotoxy(30, 1);
	textBgColor(RED, LIGHTAQUA);
	printf(" Moi ban dang nhap: \n\n");

	textBgColor(WHITE, BLACK);
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

// Kiểm tra Username tồn tại chưa?
bool checkUsername(char *Username)
{
	// Kiểm tra Username trùng với admin hay không?

	if (strcmp(Username, "admin") == 0)
		return false;

	Users A;
	FILE *f = fopen(_DIR_DATA_FOLDER_USER, "rb");

	if (f == NULL)
		return 0;

	while (fread(&A, sizeof(Users), 1, f) != 0)
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
	scanf("%s", A.Password);

	getchar();
	printf("Nhap Ho va Ten: ");
	gets(A.Fullname);

	getBirthday(A.Birthday);

	getchar();
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

	Sleep(1000);

	FILE *f = fopen(_DIR_DATA_FOLDER_USER, "ab");

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

	if (f == NULL )
		return;

	fread(&curUser, sizeof(Users), 1, f);
	do
	{
		system(cls);
		textBgColor(PURPLE, LIGHTAQUA);
		printf("------------------------------------------------------------------------------------\n");
		printf("|----------------------------------------------------------------------------------|\n");
		printf("||                          >> THAY DOI MAT KHAU <<                               ||\n");
		printf("|----------------------------------------------------------------------------------|\n");
		printf("------------------------------------------------------------------------------------\n");

		textBgColor(WHITE, BLACK);
		printf("Moi ban nhap mat khau cu: ");
		scanf("%s", oldPassword);

		printf("Moi ban nhap mat khau moi: ");
		scanf("%s", newPassword1);

		printf("Moi ban xac nhan mat khau moi: ");
		scanf("%s", newPassword2);

		if (strcmp(oldPassword, curUser.Password) != 0) // Mật khẩu không khớp với mật khẩu đã tạo
		{
			textBgColor(RED, BLACK);
			printf("Ban da nhap sai mat khau cu.\n");
			Sleep(500);
		}

		if (strcmp(newPassword1, newPassword2) != 0) // Mật khẩu xác nhận không khớp với mật khẩu vừa nhập
		{
			textBgColor(RED, BLACK);
			printf("Mat khau xac nhan khong khop.\n");
			Sleep(500);
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

	textBgColor(RED, BLACK);
	printf("Ban da doi mat khau thanh cong!\n");
	textBgColor(WHITE, BLACK);
	Sleep(1000);

	delete[] oldPassword;
	delete[] newPassword1;
	delete[] newPassword2;

}

// Hàm xem thông tin cá nhân
void viewProfile()
{
	Users curUser;

	FILE *fCur = fopen(_DIR_DATA_FOLDER_USER_CUR, "rb");

	if (fCur == NULL)
		return;

	fread(&curUser, sizeof(Users), 1, fCur);

	system(cls);
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                       >> CAP NHAT THONG TIN CA NHAN <<                         ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
	printf("Thong tin ca nhan cua Username %s:\n\n", curUser.Username);
	printf("--------------------------------------------------------\n");
	printf("Ho va ten: %s\n", curUser.Fullname);
	printf("Ngay sinh: ");
	printfDay(curUser.Birthday);
	printf("CMND: %s\n", curUser.NationID);
	printf("Dia chi: %s\n", curUser.Address);
	printf("Gioi tinh (nam la 1, nu la 0): %s\n", (curUser.Sex == 0 ? "Nu" : "Nam"));
	printf("--------------------------------------------------------\n");

	fclose(fCur);
}


// Hàm hỏi người dùng muốn chỉnh sửa nữa không?
int wantEdit()
{
	int edit = 0;
	do
	{
		textBgColor(YELLOW, BLACK);
		printf("Ban con muon chinh sua nua khong? Nhap 0 (Khong), Nhap 1 (Co): ");
		scanf("%d", &edit);
		if (edit == 1)
			return 1;
		else if (edit == 0)
			return 0;
		else
		{
			textBgColor(RED, BLACK);
			printf("Vui long nhap 0 hoac 1.\n");
		}
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

	FILE *fCur = fopen(_DIR_DATA_FOLDER_USER_CUR, "rb");

	if (fCur == NULL)
		return;

	fread(&curUser, sizeof(Users), 1, fCur);

	bool end = false;
	int edit;

	do
	{
		printf("1. Ho va ten \t 2. Ngay sinh \t 3. CMND \t 4. Dia chi \t 5. Gioi tinh\n");
		/*printf("Nhap so de chinh sua thong tin tuong ung: ");
		scanf("%d", &choice);*/

		switch (choice = getNumberPressKey(5,0))
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
			getBirthday(curUser.Birthday);

			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 3:
			getNationalID(curUser.NationID);

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
			getSex(curUser.Sex);

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

	FILE *fw = fopen(_DIR_DATA_FOLDER_USER_CUR, "wb"); // cập nhật lại thông tin trong file currentUser

	if (fw == NULL)
		return;

	fwrite(&curUser, sizeof(Users), 1, fw);
	fclose(fw);

	updateFile(curUser);
	textBgColor(RED, BLACK);
	printf("Ban da thay doi thong tin thanh cong!\n");
	Sleep(1000);
	viewProfile();
	textBgColor(YELLOW, BLACK);
	printf("Nhan phim bat ky de quay lai Menu Quan Ly Tai Khoa Ca Nhan...");
	getch();
}

void inforDecentraliseUser()
{
	Users A;

	FILE *f = fopen(_DIR_DATA_FOLDER_USER, "rb");

	if (f == NULL)
		return;

	while (fread(&A, sizeof(Users), 1, f) != 0)
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

	inforDecentraliseUser();

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
	FILE *f = fopen(_DIR_DATA_FOLDER_USER, "rb");

	if (f == NULL)
		return;

	while (fread(&A, sizeof(Users), 1, f) != 0)
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

	inforDecentraliseUser();

	delete[] Username;
}

void inforStatusUser()
{
	Users A;

	FILE *f = fopen(_DIR_DATA_FOLDER_USER, "rb");

	if (f == NULL)
		return;

	while (fread(&A, sizeof(Users), 1, f) != 0)
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
	FILE *f = fopen(_DIR_DATA_FOLDER_USER, "rb");

	if (f == NULL)
		return;

	while (fread(&A, sizeof(Users), 1, f) != 0)
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

void runMenuUser(int typeAccount)
{
	int choice = 0;
	do {
		choice = getNumberPressKey(printUserMenu(typeAccount), 0);
		switch (choice){
		case 1: // Thay đổi Password
			ChangePassword();
			break;
		case 2: // Cập nhật thông tin
			editProfile();
			break;
		case 3: // Tạo người dùng dành cho admin
			getUser(typeAccount);
			break;
		case 4: // Phân quyền người dùng
			decentraliseUser(typeAccount);
			break;
		case 5: // Chỉnh sửa trạng thái người dùng
			changeStatusUser(typeAccount);
			break;
		default:
			break;
		}
	} while (choice != 0);

}