#include "linkedListBooks.h"

// << Hàm khởi tạo danh sách và node
void Init(LLNodeBook &ls)
{
	ls.pHead = NULL;
	ls.pTail = NULL;
	ls.total = 0;
}

// Tạo 1 Node chứa data
NodeBook *makeNode(Books data){
	NodeBook *no = new NodeBook;
	no->book = data;
	no->pNext = NULL;
	no->pPrev = NULL;

	return no;
}

//======================================================

NodeBook* addAtTail(LLNodeBook &ls, Books data){ // Thêm vào cuối danh sách một struct >> Books
	NodeBook *no = makeNode(data);
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
	ls.total += data.numBook;

	return no;
}

//LLNodeBook getReaderData()
//{
//
//}

//Books *findReaderAtNumberic(LLNodeBook *lsReader, int numberic){
//	Books *reader = new Books();
//	NodeBook *pNow = InitNode();
//
//	pNow = lsReader->pHead;
//	while (pNow != NULL && numberic > 1){
//		pNow = pNow->pNext;
//		numberic--;
//	}
//
//	return pNow->reader;
//}

void freeLinkListBook(LLNodeBook &ls)
{
	NodeBook *p = ls.pHead;
	while (p != NULL)
	{
		NodeBook *q = p;
		p = p->pNext;
		delete q;
	}
	ls.pHead = NULL;
	ls.pTail = NULL;
}

//=============================================================================================
//=============================================================================================
