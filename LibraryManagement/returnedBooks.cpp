#include "returnedBooks.h"

bool findListBorrowedWithIDPerson(char *personID, LLNodeBorrowBook &lsBB){	// Tìm kiếm đọc giả theo id trả về danh sách
	BorrowBooks *infBor = new BorrowBooks;

	if (infBor == NULL)
		return false;

	FILE* fileBorrow = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "rb");

	if (fileBorrow == NULL)
	{
		return false;
	}

	while (fread(infBor, sizeof(BorrowBooks), 1 ,fileBorrow) != 0){
		if (strcmp(infBor->ID, personID) == 0)
		{
			// thêm vào danh sách
			addAtTail(lsBB, *infBor);
		}

	}

	delete infBor;
	fclose(fileBorrow);
	return true;
}

void askToPrintListBorBook(LLNodeBorrowBook llBorBook){
	switch(getNumberPressKey(askYesNoQuestion((char*)"Co muon in ra danh sach sach muon khong"), 1)){
		case 1:
			printReaderFromLL(llBorBook);
			break;
		default:
			return;
	}
}

bool returnNumberBorrwedBook(char *isbnBook, int numRet){ // trả lại kho số sách đã mượn trước đó

	FILE *fileBook = fopen(_DIR_DATA_FOLDER_BOOK, "rb");
	if (fileBook == NULL)
	{
		return false;
	}
	FILE *fileBookTemp = fopen(_DIR_DATA_FOLDER_BOOK_TEMP, "wb");
	if (fileBookTemp == NULL)
	{
		return false;
	}

	Books book;
	while (fread(&book, sizeof(Books), 1, fileBook) != 0){
		if (strcmp(book.ISBN, isbnBook) == 0)
		{
			book.numBook += numRet;	
		}
		fwrite(&book, sizeof(Books), 1, fileBookTemp);
	}

	fclose(fileBook);
	fclose(fileBookTemp);

	remove((char*)_DIR_DATA_FOLDER_BOOK);
	rename((char*)_DIR_DATA_FOLDER_BOOK_TEMP, (char*)_DIR_DATA_FOLDER_BOOK);

	return true;
}

void returnBook()
{
	printf("\n");
	char *idReader = new char[9];
	getReaderID(idReader);

	LLNodeBorrowBook llBorBook;
	Init(llBorBook); // khởi tạo danh sách

	char *nameReader = new char[31];
	for (int i = 0; i < 31; ++i)
	{
		nameReader[i] = '\0';
	}
	char *nameBook = new char[51];
	for (int i = 0; i < 51; ++i)
	{
		nameBook[i] = '\0';
	}
	long moneyPayement = 0;
	int numBor = 0;
	int numRet = 0;


	findListBorrowedWithIDPerson(idReader, llBorBook);
	if (llBorBook.pHead == NULL)
	{
		printf("Doc gia nay khong ton tai hoac khong muon sach!\n");
		Sleep(1000);
		return;
	}
	strcpy(nameReader, llBorBook.pHead->brBook.Fullname);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	char *isbnBook = new char[14];
	Books *book = new Books;
	int moneyRate = 1;
	int choice = getNumberPressKey(askYesNoQuestion((char *)"Sach co bi mat khong"),1);
	switch(choice){
		case 1: // có mất sách
			// book = findBookWithISBN(isbnBook);
			moneyRate = _SO_PHAN_TRAM_PHAT_KHI_MAT;
			printf("\n");
			printReaderFromLL(llBorBook);
			printf("Chon sach da mat <Nhap ISBN>: ");
			
			break;
		default: // không bị mất sách
			moneyRate = _SO_TIEN_PHAT;
			printf("\n");
			askToPrintListBorBook(llBorBook);

			break;
	}

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	getISBN(isbnBook);
	transformLLBorrowedBookWithISBN(llBorBook, isbnBook);
	if (llBorBook.pHead == NULL)
	{
		printf("Doc gia nay khong muon cuon sach nay trong thu vien!\n");
		Sleep(1000);
		return;
	}
	askToPrintListBorBook(llBorBook);

	strcpy(nameBook, llBorBook.pHead->brBook.nameBook);
	numBor = llBorBook.total;
	do {
		printf("Nhap so luong sach muon tra: ");
		scanf("%d", &numRet);
		if (numRet > llBorBook.total)
		{
			printf("So luong sach tra nhieu hon so luong sach da muon!\n");
			continue;
		}
		else 
		{
			returnNumberBorrwedBook(isbnBook, numRet);
			break;
		}
	}while(true);

	if (choice == 1) // co mat sach
	{
		book = findBookWithISBN(isbnBook);
		moneyPayement = book->priceBook * numRet * moneyRate;
		updateReturnBookToList(llBorBook, numRet);
	}
	else moneyPayement = moneyRate * updateReturnBookToList(llBorBook, numRet);
	updateReturnBookToFile(llBorBook);

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	returnBookBill(nameReader, nameBook, numBor, numRet, moneyPayement);

	Sleep(1000);

	delete[] idReader;
	delete[] nameReader;
	delete[] nameBook;
	delete[] isbnBook;
	delete book;


}

void returnBookBill(char *nameReader, char *nameBook, int numBor, int numRet, long moneyPayement)
{
	char *stringMoneyPayement = intMoneyToStringMoney(moneyPayement);
	system(cls);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                          >>HOA DON TRA SACH<<                                  ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	printf("|    Ten doc gia:\t%31s                            |\n", nameReader);
	printf("|----------------------------------------------------------------------------------|\n");
	printf("|    Ten sach:                                      | So luong muon | So luong tra |\n");
	printf("|    %-47s|       %-8d|      %-8d|\n", nameBook, numBor, numRet);
	printf("|----------------------------------------------------------------------------------|\n");
	printf("|    So tien phai tra:                                      %18s     |\n", stringMoneyPayement);
	printf("|----------------------------------------------------------------------------------|\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("|                                                                                  |\n");
	printf("|     Ky va ghi ro ho ten                             Ky va ghi ro ho ten          |\n");
	printf("|        Quan Thu Vien                                   Nguoi Tra Sach            |\n");
	printf("|                                                                                  |\n");
	printf("|                                                                                  |\n");
	printf("------------------------------------------------------------------------------------\n");

	// delete stringMoneyPayement;
}

