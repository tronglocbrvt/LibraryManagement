#pragma once
#include "LibraryManagement.h"
#include "commonFunction.h"
#include "readerManagement.h"
#include "bookManagement.h"
#include "linkedListBorrowBook.h"

// Day returnBookExpectDay(Day returnBookDay); // trả về ngày trả sách dự kiến (7 ngày kể từ ngày mượn)

// bool possibleReader(Day expiredDay); // Thẻ độc giả còn hạn hay không? - 1 còn hạn; 0 là hết hạn

// void updateBookFile(Books book);

bool findListBorrowedWithIDPerson(char *personID, LLNodeBorrowBook &lsBB);	// Tìm kiếm đọc giả theo id trả về danh sách

void returnBookBill(char *nameReader, char *nameBook, int numBor, int numRet, long moneyPayement);

bool returnNumberBorrwedBook(char *isbnBook, int numRet); // trả lại kho số sách đã mượn trước đó

void returnBook();

