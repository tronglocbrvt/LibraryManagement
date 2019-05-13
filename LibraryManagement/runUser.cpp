#include "runUser.h"
#include "commonFunction.h"
#include "Menu.h"
#include "changePassword.h"
#include "changeProfile.h"
#include "createUser.h"
#include "decentraliseUsers.h"
#include "statusUser.h"

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