#pragma once


#include "LibraryManagement.h"
#include "commonFunction.h"
#include "Menu.h"

char* getNationalID();

Readers *findReaderWithNationID(char *personID);	// Tìm kiếm đọc giả theo CMND

Readers *findReaderWithName(char *&personName);	// Tìm kiếm đọc giả theo họ tên

bool findListReaderWithName(char *&personName, LLNodeReader *&lsReader); // Tìm kiếm đọc giả theo họ tên và thêm vào danh sách

Readers *getTheLastReader(); // Lấy thông tin đọc giả cuối cùng trong file, trả về null nếu file rỗng.

void printfReader(Readers reader); // in thông tin đọc giả

bool printfAllReader();	// đọc toàn bộ thông tin đọc giả từ file và in ra -> không đưa vào link list

bool printfAllReader(const LLNodeReader *&ls); // in ra thông tin đọc giả từ Link List khi đã có Link List

bool getAllReaderToLL(FILE *fileReader, LLNodeReader *&ls);	// đọc toàn bộ thông tin đọc giả từ file nhưng không in ra -> đưa vào link list

Readers *setReaderInf(char ID[]); // tạo thông tin 1 đọc gỉa

bool addAnInfToFile(const Readers *reader);	// thêm thông tin đọc giả vào file

bool editReaderInf(Readers *reader); // sửa thông tin đọc giả

int askToUpdateReaderToFile();	// cập nhật thông tin đọc giả vào file - có hỏi có chắc chắn muốn cập nhật không

	// 2 trường hợp: 1: cập nhập bằng linklist, 2: cập nhật trực tiếp

bool viewInfAReader(); // Xem thông tin của một người cụ thể

bool deleteReader(Readers *reader); // xoá một độc giả

bool editReader(Readers *&reader); // sửa thông tin độc giả >> doing here 

bool editReaderInfToFile();	// chỉnh sửa thông tin đọc giả >> hàm khởi chaỵ

bool deleteReaderInfToFile();	// xoá thông tin một độc giả - hàm khởi chạy -- lọc >> doing here

bool addNewReaderInfToFile();  // thêm độc giả vào database

void runReaderManagement(); // khởi chạy quản lý đọc giả


