#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "commonFunction.h"
#include "LibraryManagement.h"

char *getNationalID();

void printfReader(Readers reader); // in thông tin đọc giả
	// đọc toàn bộ thông tin đọc giả từ file -> không đưa vào link list
	// đọc toàn bộ thông tin đọc giả từ file -> link list

Readers setReaderInf(char *readerID); // tạo thông tin 1 đọc gỉa
	// thêm thông tin đọc giả vào file

bool editReaderInf(Readers *reader); // sửa thông tin đọc giả
	// cập nhật thông tin đọc giả vào file - có hỏi có muốn cập nhật hết không
	// 2 trường hợp: 1: cập nhập bằng linklist, 2: cập nhật trực tiếp

	// Tìm kiếm đọc giả theo CMND

	// Tìm kiếm đọc giả theo họ tên




