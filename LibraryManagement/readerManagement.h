#pragma once
#include "LibraryManagement.h"
#include "commonFunction.h"
#include "Menu.h"

Readers *findReaderWithNationID(char *personID);	// Tìm kiếm độc giả theo CMND

Readers *findReaderWithEmail(char *Email); // Tìm kiếm độc giả theo Email

Readers *findReaderWithID(char *ID);	// Tìm kiếm độc giả theo ID

bool findListReaderWithName(char *personName, LLNodeReader &lsReader); // Tìm kiếm đọc giả theo họ tên và thêm vào danh sách

void viewAllReader(); // xem thông tin độc giả trong thư viện
//
bool printReaderFromLL(LLNodeReader ls); // in ra thông tin độc giả từ Linked List
//
Readers addReader();

int askToUpdateReaderToFile();

bool writeInfReaderToFile();

void viewInfAReader(Readers reader); // Xem thông tin của một người cụ thể

bool editReader(Readers &reader); 

void editReaderToFile(); // chỉnh sửa thông tin độc giả qua mã độc giả

void deleteReaderToFile(); // xóa thông tin độc giả qua mã độc giả 

void searchNationID();

void searchFullName();

void runReaderManagement(int typeAccount); // khởi chạy quản lý đọc giả

