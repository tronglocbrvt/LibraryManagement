﻿#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_CHOICE  7

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

enum Color
{
	BLACK,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTAQUA,
	LIGHTRED,
	LIGHTPURPLE,
	LIGHTYELLOW,
	LIGHTWHITE,
};

struct Day
{
	int Date; 
	int Month;
	int Year;
};

struct Users // Cấu trúc thông tin người dùng
{
	char Username[21]; // Username tối đa 20 ký tự
	char Password[17]; // Password tối đa 16 ký tự
	char Fullname[31]; // Họ tên người dùng tối đa 30 ký tự 
	Day Birthday; 
	char NationID[13]; // CMND gồm 9 số hoặc 12 số
	char Address[101]; // Địa chỉ người dùng tối đa 100 ký tự
	int Sex; // 0: Giới tính nữ; 1: Giới tính nam
	bool Status; // Nếu Status = 1: Actived; Status = 0: Blocked
	int typeAccount; // 1 nếu là admin; 2 nếu là chuyên viên (Expert); 3 nếu là quản lý (Manager)
};

struct Readers // Cấu trúc thông tin độc giả
{
	char ID[9]; // Mã độc giả gồm 8 chữ số.
	char Fullname[31]; // Họ tên người dùng tối đa 30 ký tự  
	char NationID[13]; // CMND gồm 9 số hoặc 12 số
	Day Birthday;
	int Sex; // 0: Giới tính nữ; 1: Giới tính nam
	char Email[101]; // Email dài tối đa 100 ký tự
	char Address[101]; // Địa chỉ người dùng tối đa 100 ký tự
	Day creatCard; // Ngày lập thẻ
	Day expireCard; // Ngày hết hạn thẻ
};

struct Books
{
	char ISBN[11]; // Mã sách gồm 10 số
	char nameBook[31]; // Tên sách tối đa 30 ký tự
	char Author[31]; // Tên tác giả tối đa 30 ký tự
	char publishCompany[31]; // Tên nhà xuất bản tối đa 30 ký tự
	int yearPublish; // Năm xuất bản
	char Category; // Thể loại
	long priceBook; // Giá sách (VNĐ)
	int numBook; // Số lượng sách
};

struct BorrowBooks
{
	char ISBN[11]; // Mã sách gồm 10 số
	Day borrowBookDay; // Ngày mượn sách
	Day returnBookDay; // Ngày trả sách thực tế
};