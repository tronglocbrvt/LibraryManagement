﻿#include "linkedListBorrowBook.h"

// << Hàm khởi tạo danh sách và node
void Init(LLNodeBorrowBook &ls)
{
	ls.pHead = NULL;
	ls.pTail = NULL;
	ls.total = 0;
}

// Tạo 1 Node chứa data
NodeBorrowBook *makeNode(BorrowBooks data){
	NodeBorrowBook *no = new NodeBorrowBook;
	no->brBook = data;
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
	ls.total += data.numBook;
	return no;
}

void freeLinkListBorrowBook(LLNodeBorrowBook &ls)
{
	NodeBorrowBook *pNow = ls.pHead;
	NodeBorrowBook *pNowT;
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

void viewInfAReader(BorrowBooks brBook) // Xem thông tin của một người cụ thể
{

	printf("--------------------------------------------------------\n");
	printf("\tThong Tin Sach Muon\n");
	printf("Ho va ten:\t%s\n", brBook.Fullname);
	printf("ISBN:\t%s\n", brBook.ISBN);
	printf("Ten sach:\t%s\n", brBook.nameBook);
	printf("So sach da muon:\t%d\n", brBook.numBook);
	printf("Da muon vao ngay:\t");
	printfDay(brBook.borrowBookDay);	

	// char ID[9]; // Mã độc giả mượn sách
	// char Fullname[31]; // Tên độc giả
	// char ISBN[14]; // Mã sách gồm 13 số
	// char nameBook[51]; // Tên sách
	// int numBook; // Số lượng sách mượn
	// Day borrowBookDay; // Ngày mượn sách
	// Day returnBookDay; // Ngày trả sách dự kiến
	printf("--------------------------------------------------------\n");
}
bool printReaderFromLL(LLNodeBorrowBook llBorBook){ // in ra thông tin mượn sách từ Linked List
	NodeBorrowBook *pNow = new NodeBorrowBook;
	if (pNow == NULL)
	{
		return 0;
	}

	pNow = llBorBook.pHead;
	system(cls);
	int index = 0;
	while(pNow != NULL){
		printf("\nLan muon sach thu %d:\n", ++index);
		viewInfAReader(pNow->brBook);
		pNow = pNow->pNext;
	}

	delete pNow;
	return 1;
}
int posExistBorrowedBook(LLNodeBorrowBook llBorBook, char *isbnBook){ // tìm vị trí trong danh sách có mã số sách là isbnBook
	NodeBorrowBook *pNow = new NodeBorrowBook;
	if (pNow == NULL)
	{
		return 0;
	}

	pNow = llBorBook.pHead;

	int index = -1;
	while(pNow != NULL){
		index++;
		if (strcmp(pNow->brBook.ISBN, isbnBook) == 0)
		{
			break;
		}
	}

	delete pNow;
	return index +1;
}

bool transformLLBorrowedBookWithISBN(LLNodeBorrowBook &llBorBook, char *isbnBook){ // chuyển danh sách từ tất cả sang danh sách chỉ chứa những sách cụ thể và lưu tổng số lượng sách mượn
	NodeBorrowBook *pNow = new NodeBorrowBook;
	if (pNow == NULL)
	{
		return 0;
	}

	pNow = llBorBook.pHead;
	NodeBorrowBook *pTemp;

	while(pNow != NULL){
		if (strcmp(pNow->brBook.ISBN, isbnBook) != 0)
		{
			llBorBook.total -= pNow->brBook.numBook;
			if (pNow->pPrev == NULL) // node đầu tiên
			{
				llBorBook.pHead = pNow->pNext;
				pNow->pNext->pPrev = NULL;
			}
			else if (pNow->pNext == NULL) // node cuối
			{
				llBorBook.pTail = pNow->pPrev;
				pNow->pPrev->pNext = NULL;
			}
			else { // node giữa
				pNow->pNext->pPrev = pNow->pPrev;
				pNow->pPrev->pNext = pNow->pNext;
			}
			pTemp = pNow;
			pNow = pNow->pNext;
			delete pTemp;
			continue;
		}
		pNow = pNow->pNext;
	}

	delete pNow;
	return 1;
}
long updateReturnBookToList(LLNodeBorrowBook &llBorBook, int numReturn){ // cập nhật những sách đã trả - tức giảm số sách đang mượn trong linklist về 0 và trả về số tiền phải trả
	long moneyPayement = 0;

	NodeBorrowBook *pNow = new NodeBorrowBook;
	if (pNow == NULL)
	{
		return 0;
	}

	pNow = llBorBook.pHead;
	Day today = getToday();
	while(pNow != NULL && numReturn > 0){
		if (pNow->brBook.numBook >= numReturn)
		{
			pNow->brBook.numBook = pNow->brBook.numBook - numReturn;
			numReturn = 0;
		}
		else
		{
			pNow->brBook.numBook = numReturn - pNow->brBook.numBook;
			numReturn -= pNow->brBook.numBook;
		}
		int disDay = today - pNow->brBook.returnBookDay;
		moneyPayement += (disDay > 0) * (disDay) * (_SO_TIEN_PHAT);
		pNow = pNow->pNext;
	}

	delete pNow;
	return moneyPayement;
}
bool deleteNodeReturnInFile(BorrowBooks BorBook){ // cập nhật lại file với một thông tin mượn sách, xoá những thông tin đã trả xong sách
	FILE *fo = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "rb");
	FILE *ftemp = fopen(_DIR_DATA_FOLDER_BOOK_BORROW_TEMP, "wb");

	if (fo == NULL || ftemp == NULL)
		return 0;

	BorrowBooks BorBookTemp;
	while (fread(&BorBookTemp, sizeof(BorrowBooks), 1, fo) != 0)
	{
		//         cùng người mượn									cùng loại sách							cùng thời gian mượn
		if (strcmp(BorBookTemp.ID, BorBook.ID) == 0 && strcmp(BorBookTemp.ISBN, BorBook.ISBN) == 0 && BorBookTemp.borrowBookDay == BorBook.borrowBookDay) // tìm thông tin đã đưa vào từ danh sách
		{
			if (BorBook.numBook != 0) // nếu chưa trả hết
			{
				fwrite(&BorBook, sizeof(BorrowBooks), 1, ftemp);
				printf("1.  Name: %s  --- Book: %s  --- Count:  %d\n", BorBookTemp.Fullname, BorBookTemp.nameBook, BorBookTemp.numBook);
			}
			continue;
		}
		fwrite(&BorBookTemp, sizeof(BorrowBooks), 1, ftemp);
		printf("2.  Name: %s  --- Book: %s  --- Count:  %d\n", BorBookTemp.Fullname, BorBookTemp.nameBook, BorBookTemp.numBook);
	}
	printf(">>>>>\n");

	fclose(fo);
	fclose(ftemp);

	remove((char*)_DIR_DATA_FOLDER_BOOK_BORROW);
	rename((char*)_DIR_DATA_FOLDER_BOOK_BORROW_TEMP, (char*)_DIR_DATA_FOLDER_BOOK_BORROW);

	return 1;
}
bool updateReturnBookToFile(LLNodeBorrowBook &llBorBook){ // cập nhật lại danh sách mượn vào file, xoá những sách nào đã trả hết 
	NodeBorrowBook *pNow = new NodeBorrowBook;
	if (pNow == NULL)
	{
		return 0;
	}

	pNow = llBorBook.pHead;

	while(pNow != NULL){
		deleteNodeReturnInFile(pNow->brBook);
		pNow = pNow->pNext;
	}

	delete pNow;
	return 1;
}



