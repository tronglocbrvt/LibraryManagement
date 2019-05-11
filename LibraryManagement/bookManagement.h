#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "commonFunction.h"
#include "LibraryManagement.h"
#include "Menu.h"

char *getNationalID();

Books *findBookWithNationID(const FILE *&fileBook, char *&personID);	// Tìm kiếm cuốn sách theo ISBN

Books *findBookWithName(const FILE *&fileBook, char *&personName);	// Tìm kiếm cuốn sách theo họ tên
void findListBookWithName(const FILE *&fileBook, char *&personName, LLNodeBook *&lsBook); // Tìm kiếm cuốn sách theo họ tên và thêm vào danh sách

Books *getTheLastBook(const FILE *&fileBook); // Lấy thông tin cuốn sách cuối cùng trong file, trả về null nếu file rỗng.

void printfBook(const Books &reader); // in thông tin cuốn sách
bool printfAllBook(const FILE *&fileBook);	// đọc toàn bộ thông tin cuốn sách từ file và in ra -> không đưa vào link list

bool printfAllBook(const LLNodeBook *&ls); // int ra thông tin cuốn sách từ Link List khi đã có Link List

bool getAllBookToLL(const FILE *&fileBook, LLNodeBook *&ls);	// đọc toàn bộ thông tin cuốn sách từ file nhưng không in ra -> đưa vào link list

Books *setBookInf(char *readerID); // tạo thông tin 1 đọc gỉa
bool addAnInfToFile(const FILE *fileBook, const Books *reader);	// thêm thông tin cuốn sách vào file

bool editBookInf(Books *reader); // sửa thông tin cuốn sách

bool askToUpdateBookToFile();	// cập nhật thông tin cuốn sách vào file - có hỏi có chắc chắn muốn cập nhật không

	// 2 trường hợp: 1: cập nhập bằng linklist, 2: cập nhật trực tiếp

bool viewInfABook(FILE *fileBook); // Xem thông tin của một cuốn sách cụ thể

bool deleteBook(const FILE *&fileBook, const Books *&reader); // xoá một cuốn sách
bool editBook(Books *&reader); // sửa thông tin cuốn sách >> doing here 

bool editBookInfToFile(FILE *fileBook);	// chỉnh sửa thông tin cuốn sách >> hàm khởi chaỵ

bool deleteBookInfToFile(FILE *fileBook);	// xoá thông tin một cuốn sách - hàm khởi chạy -- lọc >> doing here

bool addNewBookInfToFile(FILE *fileBook);  // thêm cuốn sách vào database

void runBookManagement(); // khởi chạy quản lý cuốn sách


