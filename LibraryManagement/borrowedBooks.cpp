#include "borrowedBooks.h"
#include "commonFunction.h"
#include "readerManagement.h"
#include "bookManagement.h"

Day returnBookExpectDay(Day borrowBookDay)
{
	Day plusDay;
	plusDay = borrowBookDay;
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
	FILE *fo = fopen("Release/Book/databaseBook.bin", "rb");
	FILE *ftemp = fopen("Release/Book/tempBook.bin", "wb");

	if (fo == NULL || ftemp == NULL)
		return;

	Books temp;

	while (fread(&temp, sizeof(Books), 1, fo) != NULL)
	{
		if (strcmp(book.ISBN, temp.ISBN) != 0)
			fwrite(&temp, sizeof(Books), 1, ftemp);
		else
			fwrite(&book, sizeof(Books), 1, ftemp);
	}
	
	fclose(fo);
	fclose(ftemp);
	remove((char*)"Release/Book/databaseBook.bin");
	rename((char*)"Release/Book/tempBook.bin", (char*)"Release/Book/databaseBook.bin");
}

void borrowBook()
{
	// Nhập mã độc giả
	int flag_reader = 1;
	Readers *temp_reader = new Readers;
	do
	{
		Readers reader;
		getReaderID(reader.ID);

		temp_reader = findReaderWithID(reader.ID);

		if (temp_reader == NULL)
		{
			flag_reader = 0;
			printf("Doc gia khong ton tai.\n");
		}

		flag_reader = 1;

		if (!possibleReader(temp_reader->expireCard))
		{
			flag_reader = 0;
			printf("The doc gia het han su dung. Vui long gia han.\n");
		}

	} while (flag_reader == 0);

	// Nhập ISBN sách cần mượn
	int end = 0;
	do
	{
		int flag_book = 1;
		Books *temp_book = new Books;
		do
		{
			Books book;
			getISBN(book.ISBN);
			temp_book = findBookWithISBN(book.ISBN);

			flag_book = 1;

			if (temp_book == NULL)
			{
				flag_book = 0;
				printf("Sach khong ton tai.\n");
			}

		} while (flag_book == 0);

		int numBorrow;
		printf("Nhap so luong muon: ");
		scanf("%d", &numBorrow);

		if ((temp_book->numBook - numBorrow) >= 0)
		{
			temp_book->numBook = temp_book->numBook - numBorrow;
			updateBookFile(*temp_book);

			// lưu các thông tin mượn sách
			BorrowBooks *borrowBook = new BorrowBooks;

			strcpy(borrowBook->ID, temp_reader->ID);
			strcpy(borrowBook->Fullname, temp_reader->Fullname);
			strcpy(borrowBook->ISBN, temp_book->ISBN);
			strcpy(borrowBook->nameBook, temp_book->nameBook);
			borrowBook->numBook = numBorrow;
			borrowBook->borrowBookDay = getToday();
			borrowBook->returnBookDay = returnBookExpectDay(borrowBook->borrowBookDay);


			FILE *f = fopen("Release/BorrowBook/databaseBorrowBook.bin", "ab");

			fwrite(borrowBook, sizeof(BorrowBooks), 1, f);

			delete borrowBook;
			delete temp_book;
			fclose(f);

			printf("Muon sach thanh cong.\n");

			int borrow = wantBorrow();
			if (borrow == 0)
				end = 1;
		}
		else
		{
			printf("So luong sach trong thu vien khong du so luong.\n");
			int borrow = wantBorrow();
			if (borrow == 0)
				end = 1;
		}
	} while (end == 0);

	borrowBookBill(temp_reader->ID, temp_reader->Fullname);

	delete temp_reader;
}

void borrowBookBill(char *ID, char *Fullname)
{
	BorrowBooks borrowBook;
	FILE *f = fopen("Release/BorrowBook/databaseBorrowBook.bin", "rb");
	
	system("cls");
	printf("PHIEU MUON SACH\n\n");
	printf("----------------------------------------------------------------------------------------------\n");
	printf("             Ma doc gia: %s                   Ho va ten: %s                                 \n", ID, Fullname);
	printf("---------------------------------------------------------------------------------------------|\n");
	printf("|    ISBN     |                Ten sach                 | So luong | Ngay muon  |  Ngay tra  |\n");
	printf("----------------------------------------------------------------------------------------------\n");

	while (fread(&borrowBook, sizeof(BorrowBooks), 1, f) != NULL)
	{
		if (strcmp(borrowBook.ID, ID) == 0)
		{
			printf("|%13s|%41s|    %2d    | %2d/%2d/%4d | %2d/%2d/%4d |\n",
				borrowBook.ISBN, borrowBook.nameBook, borrowBook.numBook, borrowBook.borrowBookDay.Date, borrowBook.borrowBookDay.Month, borrowBook.borrowBookDay.Year,
				borrowBook.returnBookDay.Date, borrowBook.returnBookDay.Month, borrowBook.returnBookDay.Year);
			printf("----------------------------------------------------------------------------------------------\n");
		}
	}
	
	fclose(f);
}
