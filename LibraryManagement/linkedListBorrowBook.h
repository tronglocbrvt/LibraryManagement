#pragma once
#include "LibraryManagement.h"
#include "commonFunction.h"

//======================================================
struct NodeBorrowBook
{
	BorrowBooks brBook;
	NodeBorrowBook *pNext;
	NodeBorrowBook *pPrev;
};

struct LLNodeBorrowBook
{
	NodeBorrowBook *pHead;
	NodeBorrowBook *pTail;
	int total;
};
//======================================================
// << Hàm khởi tạo danh sách và node

void Init(LLNodeBorrowBook &ls);

NodeBorrowBook* makeNode(BorrowBooks data);
//======================================================

NodeBorrowBook* addAtTail(LLNodeBorrowBook &ls, BorrowBooks data); // Thêm vào cuối danh sách một struct >> BorrowBook

void freeLinkListBorrowBook(LLNodeBorrowBook &ls);

//=============================================================================================
//=============================================================================================

void viewInfAReader(BorrowBooks brBook); // Xem thông tin của một người cụ thể
bool printReaderFromLL(LLNodeBorrowBook llBorBook); // in ra thông tin mượn sách từ Linked List
int posExistBorrowedBook(LLNodeBorrowBook llBorBook, char *isbnBook); // tìm vị trí trong danh sách có mã số sách là isbnBook
bool transformLLBorrowedBookWithISBN(LLNodeBorrowBook &llBorBook, char *isbnBook); // chuyển danh sách từ tất cả sang danh sách chỉ chứa những sách cụ thể và trả về tổng số lượng sách mượn

long updateReturnBookToList(LLNodeBorrowBook &llBorBook, int numReturn); // chuyển danh sách từ tất cả sang danh sách chỉ chứa những sách cụ thể và trả về tổng số lượng sách mượn
bool deleteNodeReturnInFile(BorrowBooks BorBook); // xoá một node có giá trị sách mượn là 0
bool updateReturnBookToFile(LLNodeBorrowBook &llBorBook); // những node có số sách mượn là 0 thì xoá trong file
