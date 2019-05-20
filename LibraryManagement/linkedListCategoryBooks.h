#pragma once
#include "LibraryManagement.h"


struct NodeCategory
{
	char Category[41];
	int numBookPerCategory;
	NodeCategory *pNext;
	NodeCategory *pPrev;
};

struct LLNodeCategory
{
	NodeCategory *pHead;
	NodeCategory *pTail;
	int total;
};
//======================================================
// << Hàm khởi tạo danh sách và node

void Init(LLNodeCategory &ls);

NodeCategory *makeNode(char *Category, int numBookPerCategory);
//======================================================

NodeCategory* addAtTail(LLNodeCategory &ls, char *Category, int numBookPerCategory); // Thêm vào cuối danh sách một struct >> Books

void freeLinkListBook(LLNodeCategory &ls);

//=============================================================================================
//=============================================================================================

bool addBooksToExistCategory(LLNodeCategory &ls, char *Category, int numBookPerCategory);