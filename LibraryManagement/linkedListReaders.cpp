#include "linkedListReaders.h"

// << Hàm khởi tạo danh sách và node
void Init(LLNodeReader &ls)
{
	ls.pHead = NULL;
	ls.pTail = NULL;
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

NodeReader *fAddAtTail(LLNodeReader &ls, Readers data){ // Thêm vào cuối danh sách một struct >> Readers
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

	return no;
}

//LLNodeReader getReaderData()
//{
//
//}

//Readers *findReaderAtNumberic(LLNodeReader *lsReader, int numberic){
//	Readers *reader = new Readers();
//	NodeReader *pNow = InitNode();
//
//	pNow = lsReader->pHead;
//	while (pNow != NULL && numberic > 1){
//		pNow = pNow->pNext;
//		numberic--;
//	}
//
//	return pNow->reader;
//}

void freeLinkListReader(LLNodeReader &ls)
{
	NodeReader *p = ls.pHead;
	while (p != NULL)
	{
		NodeReader *q = p;
		p = p->pNext;
		delete q;
	}
	ls.pHead = NULL;
	ls.pTail = NULL;
}

//=============================================================================================
//=============================================================================================
