#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "commonFunction.h"
#include "LibraryManagement.h"


char *getNationalID();

Readers *findReaderWithNationID(FILE *fileReader, char *&personID);	// Tìm kiếm đọc giả theo CMND

Readers *findReaderWithName(FILE *fileReader, char *&personName);	// Tìm kiếm đọc giả theo họ tên

void findListReaderWithName(FILE *&fileReader, char *&personName, LLNodeReader *&lsReader); // Tìm kiếm đọc giả theo họ tên và thêm vào danh sách

Readers *getTheLastReader(FILE *fileReader); // Lấy thông tin đọc giả cuối cùng trong file, trả về null nếu file rỗng.

void printfReader(Readers reader); // in thông tin đọc giả

bool printfAllReader(FILE *fileReader);	// đọc toàn bộ thông tin đọc giả từ file và in ra -> không đưa vào link list

bool printfAllReader(const LLNodeReader *&ls); // in ra thông tin đọc giả từ Link List khi đã có Link List

bool getAllReaderToLL(FILE *fileReader, LLNodeReader *&ls);	// đọc toàn bộ thông tin đọc giả từ file nhưng không in ra -> đưa vào link list

Readers *setReaderInf(char *readerID); // tạo thông tin 1 đọc gỉa
bool addAnInfToFile(FILE *fileReader, const Readers *reader);	// thêm thông tin đọc giả vào file

bool editReaderInf(Readers *reader); // sửa thông tin đọc giả

bool askToUpdateReaderToFile();	// cập nhật thông tin đọc giả vào file - có hỏi có chắc chắn muốn cập nhật không

	// 2 trường hợp: 1: cập nhập bằng linklist, 2: cập nhật trực tiếp

bool viewInfAReader(FILE *fileReader); // Xem thông tin của một người cụ thể

bool deleteReader(FILE *fileReader, const Readers *&reader); // xoá một độc giả

bool editReader(Readers *&reader); // sửa thông tin độc giả >> doing here 

bool editReaderInfToFile(FILE *fileReader);	// chỉnh sửa thông tin đọc giả >> hàm khởi chaỵ

bool deleteReaderInfToFile(FILE *fileReader);	// xoá thông tin một độc giả - hàm khởi chạy -- lọc >> doing here

bool addNewReaderInfToFile(FILE *fileReader);  // thêm độc giả vào database

void runReaderManagement(); // khởi chạy quản lý đọc giả


