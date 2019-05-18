#include "returnedBooks.h"

Day returnBookExpectDay(Day returnBookDay)
{
	Day plusDay;
	plusDay = returnBookDay;
	plusDay.Date += 7; // Mượn tối đa 7 ngày

	while (!isPossibleDay(plusDay.Date, plusDay.Month, plusDay.Year)){
		if (plusDay.Date > numDaysOfMonth(plusDay.Month, plusDay.Year))
		{
			plusDay.Date -= numDaysOfMonth(plusDay.Month, plusDay.Year);
			if ((++plusDay.Month) > 12)
			{
				plusDay.Month = 1;
				plusDay.Year++;
			}
		}
	}

	return plusDay;
}

bool possibleReader(Day expiredDay)
{
	Day today = getToday();

	if (today.Year < expiredDay.Year)
		return 1;
	else if (today.Year > expiredDay.Year)
		return 0;
	else
	{
		if (today.Month < expiredDay.Month)
			return 1;
		else if (today.Month > expiredDay.Month)
			return 0;
		else
		{
			if (today.Date <= expiredDay.Date)
				return 1;
			else
				return 0;
		}
	}
}

void updateBookFile(Books book)
{
	FILE *fo = fopen(_DIR_DATA_FOLDER_BOOK, "rb");
	FILE *ftemp = fopen(_DIR_DATA_FOLDER_BOOK_TEMP, "wb");

	if (fo == NULL || ftemp == NULL)
		return;

	Books temp;

	while (fread(&temp, sizeof(Books), 1, fo) != 0)
	{
		if (strcmp(book.ISBN, temp.ISBN) != 0)
			fwrite(&temp, sizeof(Books), 1, ftemp);
		else
			fwrite(&book, sizeof(Books), 1, ftemp);
	}
	
	fclose(fo);
	fclose(ftemp);
	remove((char*)_DIR_DATA_FOLDER_BOOK);
	rename((char*)_DIR_DATA_FOLDER_BOOK_TEMP, (char*)_DIR_DATA_FOLDER_BOOK);
}

void returnBook()
{
	// Nhập mã độc giả
	Readers *temp_reader = new Readers;
	do
	{
		Readers reader;
		getReaderID(reader.ID);

		temp_reader = findReaderWithID(reader.ID);

		if (temp_reader == NULL)
		{
			printf("Doc gia khong ton tai.\n");
		}
		else break;

	} while(true);

	// Nhập ISBN sách cần mượn
	int end = 0;
	do
	{
		Books *temp_book = new Books;
		do
		{
			Books book;
			getISBN(book.ISBN);

			temp_book = findBookWithISBN(book.ISBN);

			if (temp_book == NULL)
			{
				printf("Sach khong ton tai.\n");
			}
			else break;

		} while (true);

		int numReturn = 0;
		printf("Nhap so luong cuon sach tra: ");
		scanf("%d", &numReturn);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		if ((temp_book->numBook - numReturn) >= 0)
		{
			temp_book->numBook = temp_book->numBook - numReturn;
			updateBookFile(*temp_book); // cập nhật file sách


			FILE *f = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "ab");

			fwrite(returnBook, sizeof(ReturnBooks), 1, f);

			delete returnBook;
			delete temp_book;
			fclose(f);

			printf("Muon sach thanh cong.\n");

			int returnBook = wantReturn();
			if (returnBook == 0)
				end = 1;
		}
		else
		{
			printf("So luong sach trong thu vien khong du so luong.\n");
			int returnBook = wantReturn();
			if (returnBook == 0)
				end = 1;
		}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	} while (end == 0);

	returnBookBill(temp_reader->ID, temp_reader->Fullname);

	Sleep(1000);

	delete temp_reader;
}

void returnBookBill(char *ID, char *Fullname)
{
	BorrowBooks returnBook;
	FILE *f = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "rb");
	
	system(cls);
	printf("\t\t\tPHIEU MUON SACH\n\n");
	printf("----------------------------------------------------------------------------------------------\n");
	printf("|             Ma doc gia: %s                   Ho va ten: %s                                 |\n", ID, Fullname);
	printf("---------------------------------------------------------------------------------------------|\n");
	printf("|    ISBN     |                Ten sach                 | So luong | Ngay muon  |  Ngay tra  |\n");
	printf("----------------------------------------------------------------------------------------------\n");

	while (fread(&returnBook, sizeof(BorrowBooks), 1, f) != 0)
	{
		if (strcmp(returnBook.ID, ID) == 0)
		{
			printf("|%13s|%41s|    %2d    | %2d/%2d/%4d | %2d/%2d/%4d |\n",
				returnBook.ISBN, returnBook.nameBook, returnBook.numBook, returnBook.returnBookDay.Date, returnBook.returnBookDay.Month, returnBook.returnBookDay.Year,
				returnBook.returnBookDay.Date, returnBook.returnBookDay.Month, returnBook.returnBookDay.Year);
			printf("----------------------------------------------------------------------------------------------\n");
		}
	}
	
	fclose(f);
}
