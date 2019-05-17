#pragma once
#include "LibraryManagement.h"
#include "commonFunction.h"
#include "readerManagement.h"
#include "bookManagement.h"

Day returnBookExpectDay(Day borrowBookDay); // trả về ngày trả sách dự kiến (7 ngày kể từ ngày mượn)

bool possibleReader(Day expiredDay); // Thẻ độc giả còn hạn hay không? - 1 còn hạn; 0 là hết hạn

void updateBookFile(Books book);

void borrowBookBill(char *ID, char *Fullname);

void borrowBook();

