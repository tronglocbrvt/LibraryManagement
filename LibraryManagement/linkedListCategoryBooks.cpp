#include "linkedListCategoryBooks.h"

// << Hàm khởi tạo danh sách và node
void Init(LLNodeCategory &ls)
{
	ls.pHead = NULL;
	ls.pTail = NULL;
	ls.total = 0;
}

// Tạo 1 Node chứa data
NodeCategory *makeNode(char* Category, int numBookPerCategory){
	NodeCategory *no = new NodeCategory;
	strcpy(no->Category, Category);
	no->numBookPerCategory = numBookPerCategory;
	no->pNext = NULL;
	no->pPrev = NULL;

	return no;
}

//======================================================

NodeCategory* addAtTail(LLNodeCategory &ls, char *Category, int numBookPerCategory){ // Thêm vào cuối danh sách một struct >> Books
	NodeCategory *no = makeNode(Category, numBookPerCategory);
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

void freeLinkListBook(LLNodeCategory &ls)
{
	NodeCategory *pNow = ls.pHead;
	while (pNow != NULL)
	{
		NodeCategory *pDel = pNow;
		pNow = pNow->pNext;
		delete pDel;
	}
	ls.pHead = NULL;
	ls.pTail = NULL;
}

//=============================================================================================
//=============================================================================================

bool addBooksToExistCategory(LLNodeCategory &ls, char *Category, int numBookPerCategory){
	NodeCategory *pNow = ls.pHead;
	while (pNow != NULL)
	{
		if (strcmp(pNow->Category, Category) == 0)
		{
			pNow->numBookPerCategory += numBookPerCategory;
			delete pNow;
			return true;
		}

		pNow = pNow->pNext;
	}
	delete pNow;
	return false;
}
