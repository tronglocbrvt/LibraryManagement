#include "analyzingLibrary.h"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllBook(LLNodeBook lsbook){ //>> ll book
	NodeBook *pNow;
	switch(getNumberPressKey(askYesNoQuestion((char*)"Co muon hien danh sach cac sach trong thu vien khong"), 1)){
		case 1:
			system(cls);
			pNow = lsbook.pHead;
			while(pNow != NULL){
				viewInfABook(pNow->book);
				pNow = pNow->pNext;
			}
			
			delete pNow;
			return true;
		default:
			return false;
	}
	return true;
}
void analyzingBook(){
	FILE *fileBook = fopen(_DIR_DATA_FOLDER_BOOK, "rb");
	if (fileBook == NULL)
	{
		return;
	}

	LLNodeBook lsbook;
	Init(lsbook);

	Books book;
	while (fread(&book, sizeof(Books), 1, fileBook) != 0){
		addAtTail(lsbook, book);
	}

	printf("So luong sach trong thu vien hien co la:\t%d\n", lsbook.total);
	Sleep(1000);
	askToPrintAllBook(lsbook);
	Sleep(1000);
	freeLinkListBook(lsbook);
	
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllCato(LLNodeCategory lsCate){ // ll catogory
	NodeCategory *pNow;
	switch(getNumberPressKey(askYesNoQuestion((char*)"Co muon hien danh sach cac doc gia trong thu vien khong"), 1)){
		case 1:
			system(cls);
			printf("------------------------------------------------------------------------------------\n");
			printf("|----------------------------------------------------------------------------------|\n");
			printf("||                         >>DANH SACH THE LOAI<<                                 ||\n");
			printf("|----------------------------------------------------------------------------------|\n");
			printf("------------------------------------------------------------------------------------\n");
			pNow = lsCate.pHead;
			while(pNow != NULL){
				printf("|\t%-41s\t:\t%6d\t\t|\n", pNow->Category, pNow->numBookPerCategory);
				pNow = pNow->pNext;
			}
			printf("|----------------------------------------------------------------------------------|\n");
			printf("------------------------------------------------------------------------------------\n");
			
			delete pNow;
			return true;
		default:
			return false;
	}

	return true;
}
void analyzingCatoBook(){
	FILE *fileBook = fopen(_DIR_DATA_FOLDER_BOOK, "rb");
	if (fileBook == NULL)
	{
		return;
	}

	LLNodeCategory lsCate;
	Init(lsCate);

	Books book;
	while (fread(&book, sizeof(Books), 1, fileBook) != 0){
		if (!addBooksToExistCategory(lsCate, book.Category, book.numBook)) // đã thêm vào danh sách nhưng thể loại đó chưa được lưu vào danh sách
		{
			addAtTail(lsCate, book.Category, book.numBook);
		}
	}

	printf("Cac the loai trong thu vien hien co la %d The loai.\n", lsCate.total);
	Sleep(1000);
	askToPrintAllCato(lsCate);
	Sleep(1000);
	freeLinkListBook(lsCate);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllReader(LLNodeReader lsreader){ // ll reader
	NodeReader *pNow;
	switch(getNumberPressKey(askYesNoQuestion((char*)"Co muon hien danh sach cac doc gia trong thu vien khong"), 1)){
		case 1:
			system(cls);
			pNow = lsreader.pHead;
			while(pNow != NULL){
				viewInfAReader(pNow->reader);
				pNow = pNow->pNext;
			}
			
			delete pNow;
			return true;
		default:
			return false;
	}

	return true;
}
void analyzingReader(){
	FILE *fileReader = fopen(_DIR_DATA_FOLDER_READER, "rb");
	if (fileReader == NULL)
	{
		return;
	}

	LLNodeReader lsreader;
	Init(lsreader);

	Readers reader;
	while (fread(&reader, sizeof(Readers), 1, fileReader) != 0){
		addAtTail(lsreader, reader);
	}

	printf("So luong doc gia dang dang ky voi Thu vien la:\t%d\n", lsreader.total);
	Sleep(1000);
	askToPrintAllReader(lsreader);
	Sleep(1000);
	freeLinkListReader(lsreader);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllSexReader(LLNodeReader lsMaleReader, LLNodeReader lsFemaleReader){ // 2 ll sex
	NodeReader *pNow;
	switch(getNumberPressKey(askYesNoQuestion((char*)"Co muon hien thi danh sach cac doc gia theo gioi tinh trong thu vien khong"), 1)){
		case 1:
			system(cls);
			printf("Danh sach doc gia nam:\n");
			pNow = lsMaleReader.pHead;
			while(pNow != NULL){
				viewInfAReader(pNow->reader);
				pNow = pNow->pNext;
			}
			Sleep(3000);
			system(cls);
			printf("Danh sach doc gia nu\n");
			pNow = lsFemaleReader.pHead;
			while(pNow != NULL){
				viewInfAReader(pNow->reader);
				pNow = pNow->pNext;
			}
			
			delete pNow;
			return true;
		default:
			return false;
	}

	return true;
}
void analyzingSexReader(){
	FILE *fileReader = fopen(_DIR_DATA_FOLDER_READER, "rb");
	if (fileReader == NULL)
	{
		return;
	}

	LLNodeReader lsMaleReader;
	LLNodeReader lsFemaleReader;
	Init(lsMaleReader);
	Init(lsFemaleReader);

	Readers reader;
	while (fread(&reader, sizeof(Readers), 1, fileReader) != 0){
		if (reader.Sex == 1)
		{
			addAtTail(lsMaleReader, reader);	
		}
		else
		{
			addAtTail(lsFemaleReader, reader);	
		}
	}

	printf("Thu vien co %d doc gia nam va co %d doc gia nu.\n", lsMaleReader.total, lsFemaleReader.total);
	Sleep(1000);
	askToPrintAllSexReader(lsMaleReader, lsFemaleReader);
	Sleep(1000);
	freeLinkListReader(lsMaleReader);
	freeLinkListReader(lsFemaleReader);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllBorrowingBook(LLNodeBorrowBook lsBorBook){ // ll borrowbook
	NodeBorrowBook *pNow;
	switch(getNumberPressKey(askYesNoQuestion((char*)"Co muon hien danh sach cac sach dang duoc muon trong thu vien khong"), 1)){
		case 1:
			system(cls);
			pNow = lsBorBook.pHead;
			while(pNow != NULL){
				viewInfAReader(pNow->brBook);
				pNow = pNow->pNext;
			}
			
			delete pNow;
			return true;
		default:
			return false;
	}

	return true;
}
void analyzingBorrowingBook(){
	FILE *fileBorBook = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "rb");
	if (fileBorBook == NULL)
	{
		return;
	}

	LLNodeBorrowBook lsBorBook;
	Init(lsBorBook);

	BorrowBooks borBook;
	while (fread(&borBook, sizeof(BorrowBooks), 1, fileBorBook) != 0){
		addAtTail(lsBorBook, borBook);
	}

	printf("So luong sach ma doc gia dang muon trong thu vien hien co la:\t%d\n", lsBorBook.total);
	Sleep(1000);
	askToPrintAllBorrowingBook(lsBorBook);
	Sleep(1000);
	freeLinkListBorrowBook(lsBorBook);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllOverdueReader(LLNodeBorrowBook lsBorBook){ // ll borrowbook
	NodeBorrowBook *pNow;
	switch(getNumberPressKey(askYesNoQuestion((char*)"Co muon hien thi danh sach cac doc gia dang bi tre han tra sach trong thu vien khong"), 1)){
		case 1:
			system(cls);
			pNow = lsBorBook.pHead;
			while(pNow != NULL){
				viewInfAReader(pNow->brBook);
				pNow = pNow->pNext;
			}
			
			delete pNow;
			return true;
		default:
			return false;
	}

	return true;
}
void analyzingOverdueReader(){
	FILE *fileBorBook = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "rb");
	if (fileBorBook == NULL)
	{
		return;
	}

	LLNodeBorrowBook lsBorBook;
	Init(lsBorBook);

	BorrowBooks borBook;
	Day today = getToday();
	while (fread(&borBook, sizeof(BorrowBooks), 1, fileBorBook) != 0){
		if (today - borBook.returnBookDay > 0)
		{
			addAtTail(lsBorBook, borBook);
		}
	}
	printf("So luong doc gia trong thu vien dang bi tre han tra sach:\t%d\n", lsBorBook.total);
	Sleep(1000);
	askToPrintAllOverdueReader(lsBorBook);
	Sleep(1000);
	freeLinkListBorrowBook(lsBorBook);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void runningAnalyzingForAdmin(){
	int choice = 0;
	do {
		choice = getNumberPressKey(analyzingMenu(), 0);
		system(cls);
		switch (choice){
		case 1: // Thống kê số lượng sách trong thư viện v
			analyzingBook();
			break;
		case 2: // Thống kê số lượng sách theo thể loại
			analyzingCatoBook();
			break;
		case 3: // Thống kê số lượng độc giả v
			analyzingReader();
			break;
		case 4: // Thống kê số lượng độc giả theo giới tính v
			analyzingSexReader();
			break;
		case 5: // Thống kê số sách đang được mượn v
			analyzingBorrowingBook();
			break;
		case 6: // Thống kê danh sách độc giả bị trễ hạn v
			analyzingOverdueReader();
			break;
		default:
			break;
		}
		// Sleep(1000);
	} while (choice != 0);
}
void runningAnalyzingForExpert(){
	
}
void runningAnalyzingForManager(){
	
}

void runningAnalyzing(int typeAccount){
	switch(typeAccount){
		case 1: // admin
			runningAnalyzingForAdmin();
			break;
		case 2: // chuyên viên
			runningAnalyzingForExpert();
			break;
		default: // quản lý
			runningAnalyzingForManager();
			break;
	}

}