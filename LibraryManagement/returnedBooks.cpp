#include "returnedBooks.h"

// Day returnBookExpectDay(Day returnBookDay)
// {
// 	Day plusDay;
// 	plusDay = returnBookDay;
// 	plusDay.Date += 7; // Mượn tối đa 7 ngày

// 	while (!isPossibleDay(plusDay.Date, plusDay.Month, plusDay.Year)){
// 		if (plusDay.Date > numDaysOfMonth(plusDay.Month, plusDay.Year))
// 		{
// 			plusDay.Date -= numDaysOfMonth(plusDay.Month, plusDay.Year);
// 			if ((++plusDay.Month) > 12)
// 			{
// 				plusDay.Month = 1;
// 				plusDay.Year++;
// 			}
// 		}
// 	}

// 	return plusDay;
// }

// bool possibleReader(Day expiredDay)
// {
// 	Day today = getToday();

// 	if (today.Year < expiredDay.Year)
// 		return 1;
// 	else if (today.Year > expiredDay.Year)
// 		return 0;
// 	else
// 	{
// 		if (today.Month < expiredDay.Month)
// 			return 1;
// 		else if (today.Month > expiredDay.Month)
// 			return 0;
// 		else
// 		{
// 			if (today.Date <= expiredDay.Date)
// 				return 1;
// 			else
// 				return 0;
// 		}
// 	}
// }

// void updateBookFile(Books book)
// {
// 	FILE *fo = fopen(_DIR_DATA_FOLDER_BOOK, "rb");
// 	FILE *ftemp = fopen(_DIR_DATA_FOLDER_BOOK_TEMP, "wb");

// 	if (fo == NULL || ftemp == NULL)
// 		return;

// 	Books temp;

// 	while (fread(&temp, sizeof(Books), 1, fo) != 0)
// 	{
// 		if (strcmp(book.ISBN, temp.ISBN) != 0)
// 			fwrite(&temp, sizeof(Books), 1, ftemp);
// 		else
// 			fwrite(&book, sizeof(Books), 1, ftemp);
// 	}
	
// 	fclose(fo);
// 	fclose(ftemp);
// 	remove((char*)_DIR_DATA_FOLDER_BOOK);
// 	rename((char*)_DIR_DATA_FOLDER_BOOK_TEMP, (char*)_DIR_DATA_FOLDER_BOOK);
// }

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
		printf("Doc gia nay khong ton tai hoac khong muon sach\n");
		Sleep(1000);
		return;
	}
	strcpy(nameReader, llBorBook.pHead->brBook.Fullname);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	char *isbnBook = new char[14];
	switch(getNumberPressKey(askYesNoQuestion((char *)"Sach co bi mat khong"),1)){
		case 1: // có mất sách
			printf("\n");
			printReaderFromLL(llBorBook);
			printf("Chon sach da mat <Nhap ISBN>: ");
			getISBN(isbnBook);
			break;
		default: // không bị mất sách
			printf("\n");
			askToPrintListBorBook(llBorBook);
			getISBN(isbnBook);
			transformLLBorrowedBookWithISBN(llBorBook, isbnBook);
			askToPrintListBorBook(llBorBook);

			strcpy(nameBook, llBorBook.pHead->brBook.nameBook);
			numBor = llBorBook.total;

			printf("Nhap so luong sach muon tra: ");
			scanf("%d", &numRet);

			moneyPayement = updateReturnBookToList(llBorBook, numRet);
			//>>>
			askToPrintListBorBook(llBorBook);
			//<<<
			updateReturnBookToFile(llBorBook);
			break;
	}

	returnBookBill(nameReader, nameBook, numBor, numRet, moneyPayement);

	Sleep(1000);

	delete[] idReader;
	delete[] nameReader;
	delete[] nameBook;
	delete[] isbnBook;


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

	delete stringMoneyPayement;
}

