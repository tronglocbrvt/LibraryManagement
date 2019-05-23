#pragma once
#include "LibraryManagement.h"
#include "commonFunction.h"
#include "Menu.h"
#include "linkedListBooks.h"

Books *findBookWithISBN(char *ISBN);	// Tìm kiếm sách theo ISBN

bool findListBooksWithName(char *bookName, LLNodeReader &lsBook); // Tìm kiếm sách theo tên sách và thêm vào danh sách

void viewAllBook(); // xem thông tin sách trong thư viện

bool printBookFromLL(LLNodeReader ls); // in ra thông tin sách từ Linked List

Books addBook();

int askToUpdateBookToFile();

bool writeInfBookToFile();

void viewInfABook(Books book); // Xem thông tin sách

bool editBook(Books &book);

void editBookToFile(); // chỉnh sửa thông tin sách qua ISBN

void deletBookToFile(); // xóa thông tin sách qua ISBN

void searchISBN();

void searchBookName();

void runBookManagementForAdmin();
void runBookManagementForExpert();
void runBookManagementForManager();
void runBookManagement(int typeAccount); // khởi chạy quản lý sách

