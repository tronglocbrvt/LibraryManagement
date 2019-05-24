#include "userManagement.h"
#include "commonFunction.h"
#include "Menu.h"
#include "readerManagement.h"
#include "bookManagement.h"
#include "borrowedBooks.h"
#include "returnedBooks.h"
#include "analyzingLibrary.h"

//  Kiểm tra Username và Password có trong database hay không?
int checkLogin(char *Username, char *Password)
{
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
void Logout(int &typeAccount)
{
	remove((char*)_DIR_DATA_FOLDER_USER_CUR);
	textBgColor(RED, BLACK);
	printf("Ban da dang xuat thanh cong!\n");
	Sleep(1000);
	system(cls);
	typeAccount = Login();

}

void Menu(int &typeAccount)
{
	bool continueSwit = true;
	while (continueSwit){
		int choice = printLoginMenu();
		switch (choice){
		case 0:
			continueSwit = false;
			system(cls);
			return;
		case 1:
			runMenuUser(typeAccount);
			break;
		case 2:
			runReaderManagement(typeAccount);
			break;
		case 3:
			runBookManagement(typeAccount);
			break;
		case 4:
			borrowBook();
			break;
		case 5:
			returnBook();
			break;
		case 6:
			runningAnalyzing(typeAccount);
			break;
		case 7:
			continueSwit = false;
			Logout(typeAccount);
			break;
		default:
			break;
		}
	}
}
/* Hàm đăng nhập, nếu đăng nhập thành công thì trả về
1: Admin
2: Chuyên viên
3: Quản lý
Hàm đăng nhập thất bại trả về 0
*/
int Login()
{
	showTitleHeader();
	textBgColor(YELLOW, BLACK);
	gotoxy(30, 7);
	printf("MOI BAN DANG NHAP: \n");
	textBgColor(WHITE, BLACK);
	printf("Nhap ten tai khoan: ");
	char *username = new char[21];
	if (username == NULL)
		return -1;
	scanf("%s", username);

	printf("Nhap mat khau: ");
	char *password = new char[17];
	if (password == NULL)
		return -1;
	
	encryptPassword(password);

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
			return 0;
		}
	}

	fclose(f);

	return 1;
}

// Nhập thông tin người dùng
Users addUser()
{
	system(cls);
	showTitleCreatUser();

	Users A;

	getUsername(A.Username);

	printf("Nhap Password (toi da 16 ky tu): ");
	scanf("%s", A.Password);

	flushall();
	printf("Nhap Ho va Ten: ");
	gets(A.Fullname);

	getBirthday(A.Birthday); // Nhập ngày sinh

	getNationalID(A.NationID); // Nhập CMND

	printf("Nhap dia chi: ");
	gets(A.Address);

	getSex(A.Sex); // Nhập giới tính

	getStatus(A.Status); // Nhập tình trạng

	getTypeAccount(A); // Nhập loại người dùng

	return A;
}

// Ghi vào file thông tin người dùng
void writeInfUsertoFile()
{
	Users A = addUser();

	FILE *f = fopen(_DIR_DATA_FOLDER_USER, "ab");

	if (f == NULL)
		return;

	fwrite(&A, sizeof(Users), 1, f);
	fclose(f);
}

// Tạo người dùng
void getUser()
{
	/* ghi vào file người dùng mới */
	writeInfUsertoFile();
	textBgColor(RED, BLACK);
	printf("Tao nguoi dung thanh cong!\n");
	Sleep(1000);
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
void changePassword()
{
	Users curUser;
	char *oldPassword = new char[16];
	char *newPassword1 = new char[16];
	char *newPassword2 = new char[16];

	FILE *f = fopen(_DIR_DATA_FOLDER_USER_CUR, "rb"); // mở File chứa thông tin tài khoản đang đăng nhập

	if (oldPassword == NULL || newPassword1 == NULL || newPassword2 == NULL || f == NULL)
		return;

	fread(&curUser, sizeof(Users), 1, f);
	do
	{
		system(cls);
		showTitleChangePassUser();
		printf("Moi ban nhap mat khau cu: ");
		encryptPassword(oldPassword);

		printf("Moi ban nhap mat khau moi: ");
		encryptPassword(newPassword1);

		printf("Moi ban xac nhan mat khau moi: ");
		encryptPassword(newPassword2);

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
	showTitleAfterEditUser();
	printf("                         >> %-21s                          \n", curUser.Username);
	printf("|----------------------------------------------------------------------------------|\n");
	textBgColor(WHITE, BLACK);
	printf("--------------------------------------------------------\n");
	printf("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n");
	printf("|^   Ten:\t%-31s CMND:\t%-23s   v|\n", curUser.Fullname, curUser.NationID);
	printf("|^   Ngay sinh:\t\t%2d . %2d . %4d\t|  \tGioi tinh:\t%-15s   v|\n", curUser.Birthday.Date, curUser.Birthday.Month, curUser.Birthday.Year, (curUser.Sex == 1 ? (char*)"Nam" : (char*)"Nu"));
	printf("|^   Dia chi:\t%-63s   v|\n", curUser.Address);
	printf("|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|\n");
	showFooter();

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
		textBgColor(WHITE, BLACK);
		printf("1. Ho va ten    2. Ngay sinh    3. CMND    4. Dia chi    5. Gioi tinh    0. Quay ve\n");
		
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
		case 0:
			fclose(fCur);
			return;
			break;
		default:
			printf("Vui long nhap tu 0 den 5.\n");
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
	stopSceen();
}

// Hàm in thông tin quyền người dùng
void inforDecentraliseUser()
{
	Users A;

	FILE *f = fopen(_DIR_DATA_FOLDER_USER, "rb");

	if (f == NULL)
		return;

	system(cls);
	showTitleDecentraliseUser();
	printf("Danh sach Username va quyen hien tai la:\n");
	textBgColor(WHITE, BLACK);

	while (fread(&A, sizeof(Users), 1, f) != 0)
	{
		if (A.typeAccount == 2)
			printf("%s                  %s\n", A.Username, "Chuyen vien");
		else if (A.typeAccount == 3)
			printf("%s                  %s\n", A.Username, "Quan li");
	}

	fclose(f);
}

// Phân quyền người dùng
void decentraliseUser()
{
	inforDecentraliseUser(); // In thông tin quyền người dùng

	char *Username = new char[21];
	if (Username == NULL)
		return;
	int flag;

	do
	{
		textBgColor(WHITE, BLACK);
		printf("\nNhap Username ban muon phan quyen: ");
		scanf("%s", Username);

		flag = checkUsername(Username); // flag = 0: tìm thấy Username; flag = 1: không tìm thấy Username.
		if (flag == 1)
		{
			textBgColor(RED, BLACK);
			printf("Khong tim thay Username ban da nhap. Vui long thu lai.\n");
			Sleep(1000);
		}
		if (strcmp(Username, "admin") == 0)
		{
			textBgColor(RED, BLACK);
			printf("Ban khong the phan quyen cho admin.\n");
			Sleep(1000);
		}
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

	textBgColor(RED, BLACK);
	printf("Ban da phan quyen thanh cong!\n");
	Sleep(1000);

	inforDecentraliseUser(); // In thông tin quyền người dùng sau khi phân quyền
	stopSceen();
	delete[] Username;
}

// Xem thông tin trạng thái người dùng
void inforStatusUser()
{
	Users A;

	FILE *f = fopen(_DIR_DATA_FOLDER_USER, "rb");

	if (f == NULL)
		return;

	system(cls);
	showTitleStatusUser();
	printf("Danh sach Username va trang thai hien tai la:\n");
	textBgColor(WHITE, BLACK);

	while (fread(&A, sizeof(Users), 1, f) != 0)
	{
		if (A.Status == 0)
		{
			printf("%s                  %s\n", A.Username, "Blocked");
		}
		else if (A.Status == 1)
		{
			printf("%s                  %s\n", A.Username, "Actived");
		}
	}

	fclose(f);
}

// Chỉnh sửa trạng thái người dùng
void changeStatusUser()
{
	inforStatusUser(); //in thông tin trạng thái người dùng

	char *Username = new char[21];
	if (Username == NULL)
		return;
	int flag;

	do
	{
		textBgColor(WHITE, BLACK);
		printf("\nNhap Username ban muon thay doi trang thai: ");
		scanf("%s", Username);

		flag = checkUsername(Username); // flag = 0: tìm thấy Username; flag = 1: không tìm thấy Username.
		if (flag == 1)
		{
			textBgColor(RED, BLACK);
			printf("Khong tim thay Username ban da nhap. Vui long thu lai.\n");
			Sleep(1000);
		}
		if (strcmp(Username, "admin") == 0)
		{
			textBgColor(RED, BLACK);
			printf("Ban khong the thay doi trang thai cho admin.\n");
			Sleep(1000);
		}
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

	textBgColor(RED, BLACK);
	printf("Ban da cap nhat trang thai thanh cong!\n");
	Sleep(1000);
	 
	inforStatusUser(); // in lại thông tin trạng thái người dùng sau khi chỉnh sửa
	stopSceen();

	delete[] Username;
}

// Chạy chức năng 1 - Quản lý người dùng
void runMenuUser(int typeAccount)
{
	int choice = 0;
	do {
		choice = getNumberPressKey(printUserMenu(typeAccount), 0);
		switch (choice){
		case 1: // Thay đổi Password
			changePassword();
			break;
		case 2: // Cập nhật thông tin
			editProfile();
			break;
		case 3: // Tạo người dùng 
			if (typeAccount == 1)
			getUser();
			break;
		case 4: // Phân quyền người dùng
			if (typeAccount == 1)
			decentraliseUser();
			break;
		case 5: // Chỉnh sửa trạng thái người dùng
			if (typeAccount == 1)
			changeStatusUser();
			break;
		default:
			break;
		}
	} while (choice != 0);

}