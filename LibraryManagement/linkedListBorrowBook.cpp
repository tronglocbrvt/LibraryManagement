#include "linkedListBorrowBook.h"

// << Hàm khởi tạo danh sách và node
void Init(LLNodeBorrowBook &ls)
{
	ls.pHead = NULL;
	ls.pTail = NULL;
}

// Tạo 1 Node chứa data
NodeBorrowBook *makeNode(BorrowBooks data){
	NodeBorrowBook *no = new NodeBorrowBook;
	no->borrowBook = data;
	no->pNext = NULL;
	no->pPrev = NULL;

	return no;
}

//======================================================

NodeBorrowBook* addAtTail(LLNodeBorrowBook &ls, BorrowBooks data){ // Thêm vào cuối danh sách một struct >> BorrowBooks
	NodeBorrowBook *no = makeNode(data);
	if (no == NULL)
	{
		return NULL;
	}

	// Tạo liên kết
	no->pPrev = ls.pTail;
	no->pNext = NULL;
	if (ls.pTail == NULL) // nếu danh sách rỗng
	{
		ls.pHead = no;
	}
	else {
		ls.pTail->pNext = no;
	}
	ls.pTail = no;

	return no;
}

void freeLinkListBorrowBook(LLNodeBorrowBook &ls)
{
	NodeBorrowBook *p = ls.pHead;
	while (p != NULL)
	{
		NodeBorrowBook *q = p;
		p = p->pNext;
		delete q;
	}
	ls.pHead = NULL;
	ls.pTail = NULL;
}

//=============================================================================================
//=============================================================================================

