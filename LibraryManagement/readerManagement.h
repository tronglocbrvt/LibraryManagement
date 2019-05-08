#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "commonFunction.h"
#include "LibraryManagement.h"


char *getNationalID();

void printfReader(const Readers &reader); // in thông tin đọc giả
bool printfAllReader(const FILE *&fileReader);	// đọc toàn bộ thông tin đọc giả từ file và in ra -> không đưa vào link list

bool printfAllReader(const LLNodeReader *&ls); // int ra thông tin đọc giả từ Link List khi đã có Link List

bool getAllReaderToLL(const FILE *&fileReader, LLNodeReader *ls){	// đọc toàn bộ thông tin đọc giả từ file nhưng không in ra -> đưa vào link list

}
Readers *setReaderInf(char *readerID); // tạo thông tin 1 đọc gỉa
bool addInfToFile(const FILE *fileReader, const Readers *reader){	// thêm thông tin đọc giả vào file

}
bool editReaderInf(Readers *reader); // sửa thông tin đọc giả

	// cập nhật thông tin đọc giả vào file - có hỏi có muốn cập nhật hết không

	// 2 trường hợp: 1: cập nhập bằng linklist, 2: cập nhật trực tiếp

	// Tìm kiếm đọc giả theo CMND

	// Tìm kiếm đọc giả theo họ tên




