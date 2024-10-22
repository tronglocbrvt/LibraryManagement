﻿#pragma once
#include "LibraryManagement.h"

//=============================================================================================
//=============================================================================================
// CHỨC NĂNG ĐĂNG NHẬP - ĐĂNG XUẤT
int checkLogin(char *Username, char *Password); //  Kiểm tra Username và Password có trong database hay không? 

void Logout(int &typeAccount); // Hàm đăng xuất

void Menu(int &typeAccount);

int Login(); // Hàm đăng nhập

//=============================================================================================
//=============================================================================================
// CHỨC NĂNG TẠO NGƯỜI DÙNG
bool checkUsername(char *Username); // Kiểm tra Username đã tồn tại hay chưa?

Users addUser(); // Nhập các thông tin về User

void writeInfUsertoFile(); // Ghi thông tin User vào file.

void getUser(); // Tạo User

//=============================================================================================
//=============================================================================================
// CHỨC NĂNG ĐỔI PASSWORD
void updateFile(Users curUser); // Cập nhật lại file khi đã cập nhật thông tin cá nhân

void changePassword(); // Đổi Password

//=============================================================================================
//=============================================================================================
// CHỨC NĂNG CHỈNH SỬA THÔNG TIN CÁ NHÂN
void viewProfile(); // Xem thông tin cá nhân

void editProfile(); // Chỉnh sửa thông tin cá nhân

//=============================================================================================
//=============================================================================================
// CHỨC NĂNG PHÂN QUYỀN NGƯỜI DÙNG
void inforDecentraliseUser();

void decentraliseUser();

//=============================================================================================
//=============================================================================================
// CHỨC NĂNG CHỈNH SỬA TRẠNG THÁI NGƯỜI DÙNG: ACTIVATED / BLOCKED
void inforStatusUser();

void changeStatusUser();

//=============================================================================================
//=============================================================================================
// CHẠY MENU CHỨC NĂNG 1 - QUẢN LÝ NGƯỜI DÙNG
void runMenuUser(int typeAccount);