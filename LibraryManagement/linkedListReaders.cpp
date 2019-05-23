#include "linkedListReaders.h"

// << Hàm khởi tạo danh sách và node
void Init(LLNodeReader &ls)
{
	ls.pHead = NULL;
	ls.pTail = NULL;
	ls.total = 0;
}

// Tạo 1 Node chứa data
NodeReader *makeNode(Readers data){
	NodeReader *no = new NodeReader;
	no->reader = data;
	no->pNext = NULL;
	no->pPrev = NULL;

	return no;
}

//======================================================

NodeReader* addAtTail(LLNodeReader &ls, Readers data){ // Thêm vào cuối danh sách một struct >> Readers
	NodeReader *no = makeNode(data);
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
	ls.total++;

	return no;
}

void freeLinkListReader(LLNodeReader &ls)
{
	NodeReader *pNow = ls.pHead;
	NodeReader *pNowT;
	while (pNow != NULL)
	{
		pNowT = pNow;
		pNow = pNow->pNext;
		delete pNowT;
	}
	ls.pHead = NULL;
	ls.pTail = NULL;

}

//=============================================================================================
//=============================================================================================
