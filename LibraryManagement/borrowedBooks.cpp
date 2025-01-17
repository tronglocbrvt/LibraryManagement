﻿#include "borrowedBooks.h"


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

bool checkBookIsBorrowed(BorrowBooks borBook){
	FILE *fileBB = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "rb");
	if (fileBB == NULL)
		return 0;

	BorrowBooks borrowBook;
	while(fread(&borrowBook, sizeof(BorrowBooks), 1, fileBB) != 0){
		if (borrowBook == borBook)
		{
			fclose(fileBB);
			return 1;
		}
	}

	fclose(fileBB);
	return 0;
}

void borrowBook()
{
	system(cls);
	showTitleBorrow();
	// Nhập mã độc giả
	int flag_reader = 1;

	Readers *temp_reader = new Readers;
	if (temp_reader == NULL)
		return;
	do
	{
		Readers reader;
		getReaderID(reader.ID);

		temp_reader = findReaderWithID(reader.ID);

		if (temp_reader == NULL)
		{
			flag_reader = 0;
			textBgColor(RED, BLACK);
			printf("Doc gia khong ton tai.\n");
			Sleep(1000);
			return;
		}

		flag_reader = 1;

		if (!possibleReader(temp_reader->expireCard))
		{
			flag_reader = 0;
			textBgColor(RED, BLACK);
			printf("The doc gia het han su dung. Vui long gia han.\n");
			Sleep(1000);
		}

	} while (flag_reader == 0);

	// Nhập ISBN sách cần mượn
	int end = 0;
	do
	{
		int flag_book = 1;
		Books *temp_book = new Books;

		if (temp_book == NULL)
			return;
		do
		{
			Books book;
			textBgColor(WHITE, BLACK);
			getISBN(book.ISBN);

			temp_book = findBookWithISBN(book.ISBN);

			flag_book = 1;
			if (temp_book == NULL)
			{
				flag_book = 0;
				textBgColor(RED, BLACK);
				printf("Sach khong ton tai.\n");
			}

		} while (flag_book == 0);

		int numBorrow;
		textBgColor(WHITE, BLACK);
		printf("Nhap so luong muon: ");
		scanf("%d", &numBorrow);

		if ((temp_book->numBook - numBorrow) >= 0)
		{
			temp_book->numBook = temp_book->numBook - numBorrow;
			updateBookFile(*temp_book); // cập nhật file sách

			// lưu các thông tin mượn sách -> lưu thông tin
			BorrowBooks *borrowBook = new BorrowBooks;
			if (borrowBook == NULL)
				return; 

			strcpy(borrowBook->ID, temp_reader->ID);
			strcpy(borrowBook->Fullname, temp_reader->Fullname);
			strcpy(borrowBook->ISBN, temp_book->ISBN);
			strcpy(borrowBook->nameBook, temp_book->nameBook);
			borrowBook->numBook = numBorrow;
			borrowBook->borrowBookDay = getToday();
			borrowBook->returnBookDay = returnBookExpectDay(borrowBook->borrowBookDay);

			FILE *f;

			if (!checkBookIsBorrowed(*borrowBook))
			{
				f = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "ab");
				if (f == NULL)
					return;
				fwrite(borrowBook, sizeof(BorrowBooks), 1, f);
				fclose(f);
			}
			else
			{
				BorrowBooks borrowBookTemp;
				f = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "rb");
				FILE *fileTemp = fopen(_DIR_DATA_FOLDER_BOOK_BORROW_TEMP, "wb");
				if (f == NULL || fileTemp == NULL)
					return;

				while(fread(&borrowBookTemp, sizeof(BorrowBooks), 1, f)){
					if (borrowBookTemp == *borrowBook)
					{
						borrowBookTemp.numBook += borrowBook->numBook;
					}
					fwrite(&borrowBookTemp, sizeof(BorrowBooks), 1, fileTemp);
				}
				fclose(fileTemp);
				fclose(f);
				remove((char*)_DIR_DATA_FOLDER_BOOK_BORROW);
				rename((char*)_DIR_DATA_FOLDER_BOOK_BORROW_TEMP, (char*)_DIR_DATA_FOLDER_BOOK_BORROW);

			}

			delete borrowBook;
			delete temp_book;

			textBgColor(RED, BLACK);
			printf("Muon sach thanh cong.\n");
			Sleep(1000);
			int borrow = wantBorrow();
			if (borrow == 0)
				end = 1;
		}
		else
		{
			textBgColor(RED, BLACK);
			printf("So luong sach trong thu vien khong du so luong.\n");
			Sleep(1000);
			int borrow = wantBorrow();
			if (borrow == 0)
				end = 1;
		}
	} while (end == 0);

	borrowBookBill(temp_reader->ID, temp_reader->Fullname);

	stopSceen();

	delete temp_reader;
}

void borrowBookBill(char *ID, char *Fullname)
{
	BorrowBooks borrowBook;
	FILE *f = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "rb");
	if (f == NULL)
		return;
	
	system(cls);
	textBgColor(PURPLE, LIGHTAQUA);
	printf("------------------------------------------------------------------------------------\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("||                           >> PHIEU MUON SACH <<                                ||\n");
	printf("|----------------------------------------------------------------------------------|\n");
	printf("------------------------------------------------------------------------------------\n");
	textBgColor(WHITE, BLACK);
	printf("|        Ma doc gia: %8s          Ho va ten: %-31s  |\n", ID, Fullname);
	printf("|----------------------------------------------------------------------------------|\n");
	printf("|    ISBN     |           Ten sach            | So luong | Ngay muon  |  Ngay tra  |\n");
	printf("------------------------------------------------------------------------------------\n");

	while (fread(&borrowBook, sizeof(BorrowBooks), 1, f) != 0)
	{
		if (strcmp(borrowBook.ID, ID) == 0)
		{
			printf("|%13s|%31s|    %2d    | %2d/%2d/%4d | %2d/%2d/%4d |\n",
				borrowBook.ISBN, borrowBook.nameBook, borrowBook.numBook, borrowBook.borrowBookDay.Date, borrowBook.borrowBookDay.Month, borrowBook.borrowBookDay.Year,
				borrowBook.returnBookDay.Date, borrowBook.returnBookDay.Month, borrowBook.returnBookDay.Year);
			printf("------------------------------------------------------------------------------------\n");
		}
	}
	
	fclose(f);
}
