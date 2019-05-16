#pragma once


#include "LibraryManagement.h"
#include "commonFunction.h"
#include "Menu.h"

Readers *findReaderWithNationID(char *personID);	// Tìm kiếm độc giả theo CMND

Readers *findReaderWithEmail(char *Email); // Tìm kiếm độc giả theo Email

Readers *findReaderWithID(char *ID);	// Tìm kiếm độc giả theo ID

bool findListReaderWithName(char *personName, LLNodeReader &lsReader); // Tìm kiếm đọc giả theo họ tên và thêm vào danh sách

void viewAllReader(); // xem thông tin độc giả trong thư viện

//Readers *findReaderWithName(char *&personName);	// Tìm kiếm đọc giả theo họ tên
//
//Readers *getTheLastReader(); // Lấy thông tin đọc giả cuối cùng trong file, trả về null nếu file rỗng.
//
//void printfReader(Readers reader); // in thông tin đọc giả
//
//bool printfAllReader();	// đọc toàn bộ thông tin đọc giả từ file và in ra -> không đưa vào link list
//
bool printReaderFromLL(LLNodeReader ls); // in ra thông tin độc giả từ Linked List
//
//bool getAllReaderToLL(FILE *fileReader, LLNodeReader *&ls);	// đọc toàn bộ thông tin đọc giả từ file nhưng không in ra -> đưa vào link list
//
//Readers *setReaderInf(char ID[]); // tạo thông tin 1 đọc gỉa
//
//bool addAnInfToFile(const Readers *reader);	// thêm thông tin đọc giả vào file
//
//bool editReaderInf(Readers *reader); // sửa thông tin đọc giả
//
//int askToUpdateReaderToFile();	// cập nhật thông tin đọc giả vào file - có hỏi có chắc chắn muốn cập nhật không
//
//	// 2 trường hợp: 1: cập nhập bằng linklist, 2: cập nhật trực tiếp
//
//bool viewInfAReader(); // Xem thông tin của một người cụ thể
//
//bool deleteReader(Readers *reader); // xoá một độc giả
//
//bool editReader(Readers *&reader); // sửa thông tin độc giả >> doing here 
//
//bool editReaderInfToFile();	// chỉnh sửa thông tin đọc giả >> hàm khởi chaỵ
//
//bool deleteReaderInfToFile();	// xoá thông tin một độc giả - hàm khởi chạy -- lọc >> doing here
//
//bool addNewReaderInfToFile();  // thêm độc giả vào database
//
Readers addReader();

int askToUpdateReaderToFile();

bool writeInfReaderToFile();

void viewInfAReader(Readers reader); // Xem thông tin của một người cụ thể

void editReader(Readers &reader); 

void editReaderToFile(); // chỉnh sửa thông tin độc giả qua mã độc giả

void deleteReaderToFile(); // xóa thông tin độc giả qua mã độc giả 

void searchNationID();

void searchFullName();

void runReaderManagement(); // khởi chạy quản lý đọc giả

